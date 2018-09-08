#include <stdio.h>
#include <stdlib.h>
struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info_t working,  //info about working
                retire_info_t retired)  //info about being
                                        //retired
{
  int age;
  printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
  age = startAge + 1;
  for (; age <= startAge + working.months; age++) {
    initial = initial + initial * working.rate_of_return + working.contribution;
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, initial);
  }
  for (; age < startAge + working.months + retired.months; age++) {
    initial = initial + initial * retired.rate_of_return + retired.contribution;
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, initial);
  }
}

int main(void) {
  retire_info_t working;
  retire_info_t retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12.;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  int age = 327;
  double saving = 21345;
  retirement(age, saving, working, retired);
  return 0;
}
