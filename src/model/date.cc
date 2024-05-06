#include "date.h"

namespace s21 {

// Високосный ли год
int is_leap(int year) {
  int res = 0;
  if (year % 400 == 0) {
    res = 1;
  } else if (year % 100 == 0) {
    res = 0;
  } else if (year % 4 == 0) {
    res = 1;
  }
  return res;
}

#define FEBRUARY 2
// Количество дней в месяце
int days_in_month(int month, int year) {
  int res;
  /////////////// J   F  M    A   M   J   J  A   S   O    N  D
  int days[12] = {31, 0,  31, 30, 31, 30,
                  31, 31, 30, 31, 30, 31};  // Дней в месяце
  if (month != FEBRUARY) {
    res = days[month - 1];

  } else {
    if (is_leap(year)) {
      res = 29;
    } else {
      res = 28;
    }
  }
  return res;
}

// Количество дней в году
int days_in_year(int year) {
  int res = 365;
  if (is_leap(year)) {
    res = 366;
  }
  return res;
}

int date_is_correct(date dt) {
  return dt.year > 0 && dt.month >= 1 && dt.month <= 12 && dt.day >= 1 &&
         dt.day <= days_in_month(dt.month, dt.year);
}

// Возвращает текущую дату
date get_date() {
  time_t curr_time = time(NULL);
  struct tm* tm = localtime(&curr_time);
  date date;
  date.day = tm->tm_mday;
  date.month = tm->tm_mon + 1;
  date.year = tm->tm_year + 1900;  // Отсчет времени ведется с 1900 года
  return date;
}

date add_days(date dt, int days) {
  dt.day += days;
  int dim = days_in_month(dt.month, dt.year);
  while (dt.day > dim) {
    dt.day -= dim;
    dt = add_months(dt, 1);
    dim = days_in_month(dt.month, dt.year);
  }
  return dt;
}

date add_months(date dt, int months) {
  dt.year += (int)months / 12;
  dt.month += months % 12;
  if (dt.month > 12) {
    dt.year++;
    dt.month -= 12;
  }
  return dt;
}

// Разница в днях между датами
int date_diff(date dt1, date dt2) {
  if (date_lt(dt1, dt2)) {
    date tmp = dt1;
    dt1 = dt2;
    dt2 = tmp;
  }
  int count = 0;
  while (!date_eq(dt1, dt2)) {
    dt2 = add_days(dt2, 1);
    count++;
  }
  return count;
}

// Даты эквивалентны
int date_eq(date dt1, date dt2) {
  return dt1.day == dt2.day && dt1.month == dt2.month && dt1.year == dt2.year;
}

// Дата меньше
int date_lt(date dt1, date dt2) {
  int res = 0;
  if (dt1.year < dt2.year) {
    res = 1;
  } else if (dt1.year == dt2.year) {
    if (dt1.month < dt2.month) {
      res = 1;
    } else if (dt1.day < dt2.day) {
      res = 1;
    }
  }
  return res;
}

// Дата меньше либо равна
int date_le(date dt1, date dt2) {
  int res = 0;
  if (dt1.year < dt2.year) {
    res = 1;
  } else if (dt1.year == dt2.year) {
    if (dt1.month < dt2.month) {
      res = 1;
    } else if (dt1.day <= dt2.day) {
      res = 1;
    }
  }
  return res;
}

// Дата больше
int date_gt(date dt1, date dt2) { return !(date_le(dt1, dt2)); }

}  // namespace s21