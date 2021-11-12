#pragma once

#include <random>
#include <chrono>
#include <vector>
#include <iostream>

#include <cstdint>

#include "player.hpp"

/* https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-
 *  function-signum-sgn-in-c-c/10133700 */
template <typename T>
int
sgn (T val) {
  return (T (0) < val) - (val < T (0));
}

template <class T>
using PrimaryPlayer = Player<T>;

template <typename T = default_ctor_type>
class GameObject
{
private:
  std::uint_fast8_t m_maximum_players = 2;

  std::mt19937 m_prng_generator {
    std::chrono::system_clock::now ()
      .time_since_epoch ()
      .count ()
    };
  std::normal_distribution<std::double_t> m_distribution {0, 0.35};

  std::vector<Player<T>> m_players;
  PrimaryPlayer<T> m_primary_player;

  std::double_t
  rand ()
  {
    auto val = m_distribution (m_prng_generator);
    if (sgn (val) <= 0)
      return std::max (-1.0, val);
    return std::min (1.0, val);
  }

  friend std::ostream&
  operator<< (std::ostream& stream, GameObject& game)
  {
    stream << "// primary player: \n" << game.get_primary_player ();
    for (auto& player : game.get_players ())
    {
      stream << std::endl << player;
    }
    return stream;
  }
public:
  GameObject (PrimaryPlayer<T> player)
  {
    m_primary_player = player;
  }
  
  void
  add_player (const Player<T>& player)
  {
    m_players.push_back (player);
  }

  void
  set_maximum_players (std::uint_fast8_t n)
  {
    m_maximum_players = n;
  }

  decltype (m_maximum_players)
  get_maximum_players ()
  {
    return m_maximum_players;
  }

  decltype (m_primary_player)&
  get_primary_player ()
  {
    return m_primary_player;
  }

  decltype (m_players)&
  get_players ()
  {
    return m_players;
  }
};