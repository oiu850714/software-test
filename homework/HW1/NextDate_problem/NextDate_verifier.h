#pragma once

struct Date {
  int year;
  int month;
  int day;

  Date() {
    this->year = 0;
    this->month = 0;
    this->day = 0;
  }

  Date(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day;
  }

  bool operator==(const Date &rhs) const {
    if (this->year != rhs.year)
      return false;
    if (this->month != rhs.month)
      return false;
    if (this->day != rhs.day)
      return false;

    return true;
  }
};
const Date DATE_INVALID = {0, 0, 0};
Date NextDate_verifier(Date d);