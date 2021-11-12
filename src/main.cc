#include "generic.hpp"
#include <iostream>

void
simulate_battle (std::pair pair)
{
  Battle battle = game.initiate_battle (pair);
  do {
    BattleState state = battle.get_next_frame ();
    std::cout << state << std::endl;

    /* TODO */

  } while (!battle.is_completed ());
}

int
main ()
{
  Player<> primary_character (
    "unazed", PlayerAttributes<> (
      100 /* health  */,
      5   /* attack  */,
      5   /* defense */
      )
    );

  GameObject<> game (primary_character);
  game.set_maximum_players (3);
  
  game.add_player (Player<> {
    "some bot player lol xo"
    });
  
  game.add_player (Player<> {
    "another bot player"
    });

  for (auto& pair : game.create_random_pairings ())
    simulate_battle (pair);
  return false;
}