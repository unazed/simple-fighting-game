#pragma once

#include "player.hpp"
#include <iostream>

template <typename T = default_ctor_type>
class BaseAttack
{
private:
  const std::string m_name;
  const std::string m_description;

protected:
  const T m_base_atk;

  virtual void
  operator() (const Player<T>& player)
  { }
public:

  BaseAttack (const std::string name, const std::string description,
      const T attack)
      : m_name (name), m_description (description),
        m_base_atk (normalize (attack))
  { }
};

template <typename T = default_ctor_type>
class NormalAttack : BaseAttack<T>
{
  void
  operator() (const Player<T>& player) override
  {
    player.get_attributes ();
  }
};