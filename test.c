#include "s21_calc.h"

int main(void) {
  deposit_input input = {0};
  input.amount = 1000000.0;
  input.term_in_months = 3.0;
  input.interest_rate = 15.0;
  input.add_day = 0;
  input.add_month = 1;
  input.add_quater = 1;
  input.is_capitalization = 0;
  input.tax_rate = 13;
  deposit_output res = {0};
  res = calc_deposit(input);
  printf("interest = %f\n", res.accrued_interest);
  printf("end_deposit = %f\n", res.end_deposit);
  printf("tax = %f\n", res.tax_amount);
}

// result credit_res(double sum, int time, double percent, int mode) {
//   result res = {0};
//   double i = percent / 12 / 100;
//   time *= 12;
//   printf("i = %f\n", i);
//   if (!mode) {
//     double k = i / (1 - pow(1 + i, -time));
//     // double g = pow(1 + i, time);
//     // printf("g = %f\n", g);
//     // double v = g - 1;
//     // printf("v = %f\n", v);
//     // double k = i / v;
//     // printf("k = %f\n", k);
//     res.monthly_payment_max = k * sum;
//     res.all_payment = k * sum * time;
//     res.overpayment = sum * (k * time - 1);
//     //res.monthly_payment_max = sum * (k * time - 1);
//   } else {
//     double main = sum / time;
//     res.monthly_payment_max = main + sum * i;
//     res.monthly_payment_min = main + main * i;
//     res.overpayment = i * sum * (time + 1) / 2.;
//     res.all_payment = res.overpayment + sum;
//   }
//   return res;
// }

deposit_output calc_deposit(deposit_input deposit_input) {
  deposit_output res = {0};
  deposit_input.term_in_months *= 12;
  double time_day = deposit_input.term_in_months * 30;
  double time_quater = deposit_input.term_in_months / 4;
  double percent = deposit_input.interest_rate / 100;
  // double end_deposit;
  if (!deposit_input.is_capitalization) {
    if (!deposit_input.add_day) {
      // long double tmp = 1 + percent / 365;
      res.end_deposit =
          round(deposit_input.amount * pow(1 + percent / 365, time_day));
      // res.end_deposit = 1 + 2 * (-4);
      res.accrued_interest = res.end_deposit - deposit_input.amount;
      res.tax_amount = res.accrued_interest *
                       (deposit_input.tax_rate - deposit_input.tax_rate / 2) /
                       100;
      // int time = 0;
      // while(time != time_day) {
      //     if (time_day >= 365)  {
      //         int tmp_time = 365;
      //         res.end_deposit += deposit_input.amount * pow(1 + percent/365,
      //         tmp_time); res.tax_amount += (res.end_deposit -
      //         deposit_input.amount - 80000) * 0.13; time_day -= 365;
      //     } else {
      //         res.end_deposit += deposit_input.amount * pow(1 + percent/365,
      //         time_day); res.tax_amount += (res.end_deposit -
      //         deposit_input.amount - 80000) * 0.13;
      //     }
      // }
    }
    if (!deposit_input.add_month) {
      double tmp = percent / 12;
      res.end_deposit =
          deposit_input.amount * (pow(1 + tmp, deposit_input.term_in_months));
      // printf("res dep = %f\n", res.end_deposit);
      res.accrued_interest = res.end_deposit - deposit_input.amount;
      res.tax_amount = res.accrued_interest * (deposit_input.tax_rate / 100);
    }
    if (!deposit_input.add_quater) {
      res.end_deposit =
          deposit_input.amount * pow(1 + percent / 4, time_quater);
      res.accrued_interest = res.end_deposit - deposit_input.amount;
      res.tax_amount = res.accrued_interest * (deposit_input.tax_rate / 100);
    }
  } else {
    res.end_deposit = (deposit_input.amount * percent * (time_day / 365));
    res.accrued_interest = res.end_deposit - deposit_input.amount;
    res.tax_amount = res.accrued_interest * (deposit_input.tax_rate / 100);
  }
  return res;
}
