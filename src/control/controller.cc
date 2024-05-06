#include "controller.h"

double Controller::calculate(std::string expr, double x){
    s21::polish polish(expr);
    return polish.calc(x);
}

void Controller::calculate_vec(std::string expr, double x1, double x2, int pixels,  std::vector<double>& x,std::vector<double>& y){
    s21::polish polish(expr);

    double delta = (x2-x1)/pixels;

    x.resize(pixels);
    y.resize(pixels);
    for(int i=0; i<pixels; i++){
        x[i] = x1+delta/2. + i*delta;
        y[i]=polish.calc(x[i]);
    }
}

void Controller::differentiated_credit_calc(double credit_amount, int months, double interest_rate,
                                            s21::date* dt, s21::credit_pays& credit_pays){
    s21::differentiated_credit_calc(credit_amount,months,interest_rate,dt,credit_pays);
}

void Controller::annuity_payment_calc(double credit_amount, int months, double interest_rate,
                                      s21::credit_pays& credit_pays){
s21::annuity_payment_calc(credit_amount,months,interest_rate, credit_pays);
}

int Controller::deposit_calc(s21::date start_dt, double deposit_amount, int period, int period_type, double interest_rate, double tax_rate, int payments_periodicity,
                             int payments_periodicity_type, int interest_capitalization, std::list<s21::pay> &deposits, std::list<s21::pay> &withdrawals,
                             s21::deposit& deposit){
    return s21::deposit_calc(start_dt, deposit_amount, period,period_type, interest_rate, tax_rate, payments_periodicity,
                      payments_periodicity_type, interest_capitalization,deposits,withdrawals, deposit);

}
