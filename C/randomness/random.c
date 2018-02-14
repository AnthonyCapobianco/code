#include <stdio.h>
#include <string.h>

enum { UP = 160000
     , PATROL = 1000
     , EVENT = 2000 
     , HEROIC_MISSION = 5750
     };
int guardianCurrentXPLevel()
{
  int guardianLevel = 0;
  int valid = 0;
  do 
  {
    printf("Please insert the current level of your character: ");
    valid = scanf("%i", &guardianLevel);

  } while ( !valid || guardianLevel > UP || guardianLevel < 0);
  return guardianLevel;
}// guardianCurrentXPLevel()
int remainingHeroics()
{
  int heroicLeft = 4;
  int valid = 0;
  if (heroicLeft > 3 || heroicLeft < 0)
  {
    printf("Please insert the number of heroic Missions (Ikora) you have yet to do: ");
    valid = scanf("%i", &heroicLeft);
  }
  return heroicLeft;
}// remainingHeroics()
int menuAsk()
{
  int answer = 0;
  int valid = 0;
  do{
    printf("Which of the following perks are active on your character?\n\t"
              "1)Well Rested Perk\n\t"
              "2)Bright Paragon\n\t"
              "3)Ghost 10%% xp from public events\n\t"
              "4)None\n"
          );
    valid = scanf("%i", &answer);
  } while (answer > 4 || answer < 1 || !valid );
  
  if (answer == 1) return 30;
  else if (answer == 4) return 10;
  else return 11;
}// menuAsk()
int main(void) 
{
    int heroicsLeft = remainingHeroics();
    int currentLevel = guardianCurrentXPLevel();
    int xpToLevelUp = (UP - currentLevel)
      , xpPerPatrol = PATROL
      , xpPerPubEvt = EVENT
      , xpPerHeroic = HEROIC_MISSION
      ;
    int i
      , n
      , v
      , h
      ;
    int sum
      , sup
      ;
    float mul;
    
    mul = (menuAsk() / 10.0);
    xpPerHeroic *= (mul == 3.0) ? 3 : 1;
    xpPerPatrol *= mul;
    xpPerPubEvt *= (mul == 1.1 ? 1 : mul);
    
    for (i = 0, n = 0, v = 0, h = 0; sum != xpToLevelUp; )
    {
        if ((sum + (xpPerHeroic * heroicsLeft)) <= xpToLevelUp
           && heroicsLeft > 0)
        {
            sum += xpPerHeroic;
            --heroicsLeft;
            ++h;
        }
        else if ((sum + xpPerPubEvt) <= xpToLevelUp)
        {
            sum += xpPerPubEvt;
            ++v;
        }
        else if ((sum + xpPerPatrol) <= xpToLevelUp)
        {
            sum += xpPerPatrol;
            ++n;
        }
        else
        {
            sup = (xpToLevelUp - sum);
            sum += sup;
        }
    }
    if (h > 0)
    { 
        printf("You need to do %i heroic missions (total xp: %i) and \n", 
                h, (h * xpPerHeroic)
              );
    }
    printf("You need to do %i public events (total xp: %i) and \n", 
            v, (v * xpPerPubEvt)
          );
    printf("You need to do %i patrols (total xp: %i) and \n",
            n, (n * xpPerPatrol)
          );
    printf("A supplement of: %i xp", sup);
    return 0;
}