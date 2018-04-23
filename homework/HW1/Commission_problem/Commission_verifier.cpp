#include "Commission_verifier.h"

Commission Commission_verifier(const int Locks, const int Stocks,
                               const int Barrels) {
  const int LockPrice = 45, StockPrice = 30, BarrelPrice = 25;
  if (Locks < 1 || Locks > 70)
    return Commission(-1, -1);
  if (Stocks < 1 || Stocks > 80)
    return Commission(-1, -1);
  if (Barrels < 1 || Barrels > 90)
    return Commission(-1, -1);

  return Commission(0, 0);
}