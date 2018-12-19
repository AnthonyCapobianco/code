/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <set>
#include <array>
#include <string>

namespace fen_to_board {

struct Piece {
    const char letter;
    const std::string icon;
    
    Piece(const char c, const std::string i)
    : letter(c)
    , icon(i) {
    }
};

class Chessboard {
private:

static constexpr std::array<Piece, 12> kPieces {
  {'P', "♙"}, {'N', "♘"}, {'B', "♗"}, {'R', "♖"}, {'Q', "♕"}, {'K', "♔"}
, {'p', "♟"}, {'n', "♞"}, {'b', "♝"}, {'r', "♜"}, {'q', "♛"}, {'k', "♚"}
};

std::string m_board;

public:
  Chessboard(const std::string& kFen) noexcept(true) {
    m_board.reserve(900); 
  }
};

} // namespace FenToBoard