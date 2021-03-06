#include "Commission_verifier.h"

Commission Commission_verifier(const int Locks, const int Stocks,
                               const int Barrels) {
  const int LockPrice = 45, StockPrice = 30, BarrelPrice = 25;

  // 1st "big" if to check valid input
  if (Locks < 1 || Locks > 70)
    return Commission(-1, -1);
  if (Stocks < 1 || Stocks > 80)
    return Commission(-1, -1);
  if (Barrels < 1 || Barrels > 90)
    return Commission(-1, -1);

  int sales = Locks * LockPrice + Stocks * StockPrice + Barrels * BarrelPrice;
  double commission = 0;

  // 2dn if to check sales
  if (sales > 1800) {
    commission = 0.1 * 1000;
    commission += 0.15 * 800;
    commission += 0.20 * (sales - 1800);
  } else if (sales > 1000) {
    commission = 0.1 * 1000;
    commission += 0.15 * (sales - 1000);
  } else {
    commission = 0.1 * sales;
  }
  return Commission(sales, commission);
}