#pragma once

#include <string>
#include <type_traits>
#include <limits>
#include <iostream>

#include <cmath>
#include <cstdint>

#include "attacks.hpp"

template <typename T>
constexpr T
normalize (T val)
{
  return static_cast<T>(100.0 * val / std::numeric_limits<T>::max ());
}

template <typename T>
constexpr T
unnormalize (T val)
{
  if (!val)
    return static_cast<T>(0);
  return static_cast<T>(std::numeric_limits<T>::max () / (100.0 * val));
}

using default_ctor_type = std::uint_fast8_t;

std::ostream&
operator<< (std::ostream& stream, const std::uint_fast8_t& val)
{
  return stream << (unsigned int)val;
}

template <typename T = default_ctor_type>
class PlayerAttributes
{
  static_assert (sizeof (T) <= 4, "PlayerAttributes generic type must "
                                  "be at most 32 bits wide");
  static_assert (std::is_unsigned_v<T>, "PlayerAttributes generic type "
                                  "must be unsigned");
private:
  T m_health, m_attack, m_defense;


public:
  friend std::ostream&
  operator<< (std::ostream& stream, PlayerAttributes<T>& attrs)
  {
    return stream << "health (" << attrs.get_health () << "), "
                  << "attack (" << attrs.get_attack () << "), "
                  << "defense (" << attrs.get_defense () << ")";
  }                              

  const T
  get_health ()
  {
    return unnormalize (m_health);
  }

  void
  set_health (T val)
  {
    m_health = normalize<T> (val);
  }

  const T
  get_attack ()
  {
    return unnormalize (m_attack);
  }

  void
  set_attack (T val)
  {
    m_attack = normalize<T> (val);
  }

  const T
  get_defense ()
  {
    return unnormalize (m_defense);
  }

  void
  set_defense (T val)
  {
    m_defense = normalize<T> (val);
  }

  PlayerAttributes (T health, T attack, T defense)
      : m_health (normalize (health)),
        m_attack (normalize (attack)),
        m_defense (normalize (defense))
  { }

  PlayerAttributes ()
      : m_health (normalize (std::numeric_limits<T>::max ())),
        m_attack (0), m_defense (0)
  { }
};

template <typename T = default_ctor_type>
class Player
{
private:
  std::string m_name;
  PlayerAttributes<T> m_attrs;

public:
  friend std::ostream&
  operator<< (std::ostream& stream, Player& player)
  {
    return stream << "player name (" << player.get_name () << ")\n--- "
                  << player.get_attributes ();
  }

  Player&
  operator= (Player& other);

  Player ()
      : m_name ("n/a"), m_attrs (PlayerAttributes<T> ())
  { }

  Player (const std::string name)
      : m_name (name), m_attrs (PlayerAttributes<T> ())
  { }

  Player (const std::string name, PlayerAttributes<T> attrs)
      : m_name (name), m_attrs (attrs)
  { }

  const std::string&
  get_name () const
  {
    return m_name;
  }

  PlayerAttributes<T>&
  get_attributes ()
  {
    return m_attrs;
  }
};

template <typename T>
Player<T>&
Player<T>::operator= (Player<T>& other)
{
  m_name = other.get_name ();
  m_attrs = other.get_attributes ();
  return *this;
}