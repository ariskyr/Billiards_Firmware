#include "Arduino.h"
#include "CH926.h"

CH926::CH926(const int coinSelector, int impulsCount, int price) : m_coinSelector(coinSelector), m_impulsCount(impulsCount), m_price(price)
{
    //setup of coins, using pin 2 that enables interrupt signals
  pinMode(m_coinSelector, INPUT_PULLUP);
}

int CH926::coinCounter(int m_count)
{
  Serial.print("loop counter: ");
  Serial.print(m_count);
  Serial.print(" Impulses: ");
  Serial.print(m_impulsCount);
  Serial.print(" Amount: ");
  Serial.println(m_price);
  
    // price -> variable for specific game / resets
    // total -> variable for all games

    // 1 impulse for 2 euro coins
  if (m_count >= 30 and m_impulsCount == 1)
  {
    m_price = m_price + 2;
      // reset impulse counter
    m_impulsCount = 0;
  }
  // 2 impulses for 1 euro coins
  if (m_count >= 30 and m_impulsCount == 2)
  {
    m_price = m_price + 1;
    // reset impulse counter
    m_impulsCount = 0;
  }
  // 3 impulses for 50 cent coins
  if (m_count >= 30 and m_impulsCount == 3)
  {
    m_price = m_price + 0.5;
    // reset impulse counter
    m_impulsCount = 0;
  }
  // 4 impulses for 20 cent coins
  if (m_count >= 30 and m_impulsCount == 4)
  {
    m_price = m_price + 0.2;
    // reset impulse counter
    m_impulsCount = 0;
  }
  // 5 impulses for 10 cent coins
  if (m_count >= 30 and m_impulsCount == 5)
  {
    m_price = m_price + 0.1;
    // reset impulse counter
    m_impulsCount = 0;
  }
  return m_price;
}

void CH926::resetPrice()
{
  m_price = 0;
}
