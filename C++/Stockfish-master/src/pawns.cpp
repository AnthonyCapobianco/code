/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad
  Copyright (C) 2015-2018 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <algorithm>
#include <cassert>

#include "bitboard.h"
#include "pawns.h"
#include "position.h"
#include "thread.h"

namespace {

  // Pawn penalties
  constexpr Score Backward = make_score(9, 24);
  constexpr Score Doubled = make_score(11, 56);
  constexpr Score Isolated = make_score(5, 15);

  // Connected pawn bonus by opposed, phalanx, #support and rank
  Score Connected[2][2][3][RANK_NB];

  // Strength of pawn shelter for our king by [distance from edge][rank].
  // RANK_1 = 0 is used for files where we have no pawn, or pawn is behind our king.
  constexpr Value ShelterStrength[static_cast<int>(FILE_NB) / 2][RANK_NB] = {
    { Value( -6), Value( 81), Value( 93), Value( 58), Value( 39), Value( 18), Value(  25) },
    { Value(-43), Value( 61), Value( 35), Value(-49), Value(-29), Value(-11), Value( -63) },
    { Value(-10), Value( 75), Value( 23), Value( -2), Value( 32), Value(  3), Value( -45) },
    { Value(-39), Value(-13), Value(-29), Value(-52), Value(-48), Value(-67), Value(-166) }
  };

  // Danger of enemy pawns moving toward our king by [distance from edge][rank].
  // RANK_1 = 0 is used for files where the enemy has no pawn, or their pawn
  // is behind our king.
  constexpr Value UnblockedStorm[static_cast<int>(FILE_NB) / 2][RANK_NB] = {
    { Value( 89), Value(107), Value(123), Value(93), Value(57), Value( 45), Value( 51) },
    { Value( 44), Value(-18), Value(123), Value(46), Value(39), Value( -7), Value( 23) },
    { Value(  4), Value( 52), Value(162), Value(37), Value( 7), Value(-14), Value( -2) },
    { Value(-10), Value(-14), Value( 90), Value(15), Value( 2), Value( -7), Value(-16) }
  };

  // Danger of blocked enemy pawns storming our king, by rank
  constexpr Value BlockedStorm[RANK_NB] =
    { Value(0), Value(0), Value(66), Value(6), Value(5), Value(1), Value(15) };


  template<Color Us>
  Score evaluate(const Position& pos, Pawns::Entry* entry) {

    constexpr Color Them = (Us == WHITE ? BLACK : WHITE);
    constexpr Direction Up = (Us == WHITE ? NORTH : SOUTH);

    Bitboard b; 
    Bitboard neighbours;
    Bitboard stoppers;
    Bitboard doubled;
    Bitboard supported;
    Bitboard phalanx;
    
    Bitboard lever;
    Bitboard leverPush;
    
    Square s;
    bool opposed;
    bool backward;
    Score score = SCORE_ZERO;
    const Square* pl = pos.squares<PAWN>(Us);

    Bitboard ourPawns = pos.pieces(Us, PAWN);
    Bitboard theirPawns = pos.pieces(Them, PAWN);

    entry->passedPawns[Us] = entry->pawnAttacksSpan[Us] = entry->weakUnopposed[Us] = 0;
    entry->semiopenFiles[Us] = 0xFF;
    entry->kingSquares[Us] = SQ_NONE;
    entry->pawnAttacks[Us] = pawn_attacks_bb<Us>(ourPawns);
    entry->pawnsOnSquares[Us][BLACK] = popcount(ourPawns & DarkSquares);
    entry->pawnsOnSquares[Us][WHITE] = pos.count<PAWN>(Us) - entry->pawnsOnSquares[Us][BLACK];

    // Loop through all pawns of the current color and score each pawn
    while ((s = *pl++) != SQ_NONE) {
        assert(pos.piece_on(s) == make_piece(Us, PAWN));

        File f = file_of(s);

        entry->semiopenFiles[Us] &= ~(1 << f);
        entry->pawnAttacksSpan[Us] |= pawn_attack_span(Us, s);

        // Flag the pawn
        opposed = theirPawns & forward_file_bb(Us, s);
        stoppers = theirPawns & passed_pawn_mask(Us, s);
        lever = theirPawns & PawnAttacks[Us][s];
        leverPush = theirPawns & PawnAttacks[Us][s + Up];
        doubled = ourPawns & (s - Up);
        neighbours = ourPawns & adjacent_files_bb(f);
        phalanx = neighbours & rank_bb(s);
        supported = neighbours & rank_bb(s - Up);

        // A pawn is backward when it is behind all pawns of the same color
        // on the adjacent files and cannot be safely advanced.
        backward =  not(ourPawns & pawn_attack_span(Them, s + Up))
          and (stoppers & (leverPush | (s + Up)));

        // Passed pawns will be properly scored in evaluation because we need
        // full attack info to evaluate them. Include also not passed pawns
        // which could become passed after one or two pawn pushes when are
        // not attacked more times than defended.
        if (not(stoppers ^ lever ^ leverPush) and popcount(supported) >= popcount(lever) - 1
            and popcount(phalanx) >= popcount(leverPush)) {
          entry->passedPawns[Us] |= s;
        } else if (stoppers == SquareBB[s + Up] and relative_rank(Us, s) >= RANK_5) {
            b = shift<Up>(supported) & ~theirPawns;
            while (b) {
                if (not more_than_one(theirPawns & PawnAttacks[Us][pop_lsb(&b)]))
                    entry->passedPawns[Us] |= s;
            }
        }

        // Score this pawn
        if (supported | phalanx) {
            score += Connected[opposed][bool(phalanx)][popcount(supported)][relative_rank(Us, s)];
        } else if (not neighbours) {
            score -= Isolated, entry->weakUnopposed[Us] += !opposed;
        } else if (backward) {
            score -= Backward, entry->weakUnopposed[Us] += !opposed;
        }
        if (doubled and not supported)
          score -= Doubled;
    }
    return score;
  }

} // namespace

namespace Pawns {

/// Pawns::init() initializes some tables needed by evaluation. Instead of using
/// hard-coded tables, when makes sense, we prefer to calculate them with a formula
/// to reduce independent parameters and to allow easier tuning and better insight.

void init() {
  static constexpr int Seed[RANK_NB] = { 0, 13, 24, 18, 65, 100, 175, 330 };

  for (int opposed = 0; opposed <= 1; ++opposed)
    for (int phalanx = 0; phalanx <= 1; ++phalanx)
      for (int support = 0; support <= 2; ++support)
        for (Rank r = RANK_2; r < RANK_8; ++r) {
          int v = 17 * support;
          v += (Seed[r] + (phalanx ? (Seed[r + 1] - Seed[r]) / 2 : 0)) >> opposed;

          Connected[opposed][phalanx][support][r] = make_score(v, v * (r - 2) / 4);
        }
}


/// Pawns::probe() looks up the current position's pawns configuration in
/// the pawns hash table. It returns a pointer to the Entry if the position
/// is found. Otherwise a new Entry is computed and stored there, so we don't
/// have to recompute all when the same pawns configuration occurs again.

Entry* probe(const Position& pos) {

  Key key = pos.pawn_key();
  Entry* e = pos.this_thread()->pawnsTable[key];

  if (e->key == key)
      return e;

  e->key = key;
  e->scores[WHITE] = evaluate<WHITE>(pos, e);
  e->scores[BLACK] = evaluate<BLACK>(pos, e);
  e->openFiles = popcount(e->semiopenFiles[WHITE] & e->semiopenFiles[BLACK]);
  e->asymmetry = popcount(  (e->passedPawns[WHITE]   | e->passedPawns[BLACK])
                          | (e->semiopenFiles[WHITE] ^ e->semiopenFiles[BLACK]));

  return e;
}


/// Entry::evaluate_shelter() calculates the shelter bonus and the storm
/// penalty for a king, looking at the king file and the two closest files.

template<Color Us>
Value Entry::evaluate_shelter(const Position& pos, Square ksq) {

  constexpr Color     Them = (Us == WHITE ? BLACK : WHITE);
  constexpr Direction Down = (Us == WHITE ? SOUTH : NORTH);
  constexpr Bitboard  BlockRanks = (Us == WHITE ? Rank1BB | Rank2BB : Rank8BB | Rank7BB);

  Bitboard b = pos.pieces(PAWN) & ~forward_ranks_bb(Them, ksq);
  Bitboard ourPawns = b & pos.pieces(Us);
  Bitboard theirPawns = b & pos.pieces(Them);

  Value safety = (shift<Down>(theirPawns) & (FileABB | FileHBB) & BlockRanks & ksq) ?
                 Value(374) : Value(5);

  File center = std::max(FILE_B, std::min(FILE_G, file_of(ksq)));
  for (File f = File(center - 1); f <= File(center + 1); ++f)
  {
      b = ourPawns & file_bb(f);
      int ourRank = b ? relative_rank(Us, backmost_sq(Us, b)) : 0;

      b = theirPawns & file_bb(f);
      int theirRank = b ? relative_rank(Us, frontmost_sq(Them, b)) : 0;

      int d = std::min(f, ~f);
      safety += ShelterStrength[d][ourRank];
      safety -= (ourRank && (ourRank == theirRank - 1)) ? BlockedStorm[theirRank]
                                                        : UnblockedStorm[d][theirRank];
  }

  return safety;
}


/// Entry::do_king_safety() calculates a bonus for king safety. It is called only
/// when king square changes, which is about 20% of total king_safety() calls.

template<Color Us>
Score Entry::do_king_safety(const Position& pos, Square ksq) {

  kingSquares[Us] = ksq;
  castlingRights[Us] = pos.can_castle(Us);
  int minKingPawnDistance = 0;

  Bitboard pawns = pos.pieces(Us, PAWN);
  if (pawns)
      while (!(DistanceRingBB[ksq][++minKingPawnDistance] & pawns)) {}

  Value bonus = evaluate_shelter<Us>(pos, ksq);

  // If we can castle use the bonus after the castling if it is bigger
  if (pos.can_castle(Us | KING_SIDE))
      bonus = std::max(bonus, evaluate_shelter<Us>(pos, relative_square(Us, SQ_G1)));

  if (pos.can_castle(Us | QUEEN_SIDE))
      bonus = std::max(bonus, evaluate_shelter<Us>(pos, relative_square(Us, SQ_C1)));

  return make_score(bonus, -16 * minKingPawnDistance);
}

// Explicit template instantiation
template Score Entry::do_king_safety<WHITE>(const Position& pos, Square ksq);
template Score Entry::do_king_safety<BLACK>(const Position& pos, Square ksq);

} // namespace Pawns
