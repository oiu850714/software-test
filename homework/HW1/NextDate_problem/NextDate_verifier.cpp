#include "NextDate_verifier.h"

Date NextDate_verifier(const Date &d) {
  if (d.year < 1812 || d.year > 2012)
    return DATE_INVALID;
  if (d.month < 1 || d.month > 12)
    return DATE_INVALID;
  if (d.day < 1 || d.day > 31)
    return DATE_INVALID;

  int days_per_month = 0;
  switch (d.month) {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    days_per_month = 31;
    break;
  case 4:
  case 6:
  case 9:
  case 11:
    days_per_month = 30;
    break;
  // 28 or 29 days
  case 2:
    if (d.year % 4 != 0)
      days_per_month = 28;
    else if (d.year % 100 != 0)
      days_per_month = 29;
    else if (d.year % 400 != 0)
      days_per_month = 28;
    else
      // d.year%400 == 0
      days_per_month = 29;
    break;
  }

  if (d.day <= days_per_month - 1) {
    return Date(d.year, d.month, d.day + 1);
  } else if (d.day == days_per_month) {
    if (d.month != 12)
      return Date(d.year, d.month + 1, 1);
    return Date(d.year + 1, 1, 1);
  } else {
    return DATE_INVALID;
  }
}