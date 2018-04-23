#pragma once

class Commission {
public:
  Commission(int s, double c) : sales(s), commission(c) {}
  bool operator==(const Commission &com) const {
    if (com.sales == sales && com.commission == commission)
      return true;
    else
      return false;
  }

private:
  int sales;
  double commission;
};

const Commission INVALID_COMMISSION(-1, -1);
Commission Commission_verifier(const int Locks, const int Stocks,
                               const int Barrels);