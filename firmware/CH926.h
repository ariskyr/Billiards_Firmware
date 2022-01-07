#pragma once
#ifndef _CH926_H_
#define _CH926_H_

class CH926
{
  public:
    CH926(const int coinSelector, int impulsCount, int price);
    int coinCounter(int m_count);
    void resetPrice();
  private:
      const int m_coinSelector; 
      int m_impulsCount, m_price;
};

#endif
