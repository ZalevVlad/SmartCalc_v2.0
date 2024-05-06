#ifndef DATE_H_
#define DATE_H_

#include <time.h>

namespace s21{

    struct date {
        int day;
        int month;
        int year;

        /*
         * Bool operations
         */

        bool operator==(const date& other){
            return this->day == other.day && this->month == other.month && this->year == other.year;
        }

        bool operator<(const date& other) const{
            bool res = false;
            if (this->year < other.year) {
                res = true;
            } else if (this->year == other.year) {
                if (this->month < other.month) {
                    res = true;
                } else if (this->day < other.day) {
                    res = true;
                }
            }
            return res;
        }

        bool operator<=(const date& other) const{
            int res = 0;
            if (this->year < other.year) {
                res = 1;
            } else if (this->year == other.year) {
                if (this->month < other.month) {
                    res = 1;
                } else if (this->day <= other.day) {
                    res = 1;
                }
            }
            return res;
        }

        bool operator>(const date& other) const{
            return !(*this <= other);
        }

    };
    typedef struct date date;

    int date_is_correct(date dt);

    date get_date();
    date add_days(date dt, int days);
    date add_months(date dt, int months);

    int date_diff(date dt1, date dt2);

    int date_eq(date dt1, date dt2);
    int date_lt(date dt1, date dt2);
    int date_le(date dt1, date dt2);
    int date_gt(date dt1, date dt2);

    int days_in_month(int month, int year);
    int days_in_year(int year);

} // namespace s21

#endif  // MY_DATE_H_
