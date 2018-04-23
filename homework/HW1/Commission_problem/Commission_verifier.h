#pragma once

class Commission {
public:
  Commission(int s, double c) : sales(s), commission(c) {}
  bool operator==(const Commission &com) {
    if (com.sales == sales && com.commission == commission)
      return true;
    else
      return false;
  }

private:
  int sales;
  double commission;
};

Commission Commission_verifier(const int Locks, const int Stocks,
                               const int Barrels);