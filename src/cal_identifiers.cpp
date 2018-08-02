#include "cal_quantlib_types.hpp"
#include "cal_creation.hpp"

using namespace QuantLib;  

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::vector<bool> cal_is_weekend_cpp(List cal, std::vector<QuantLib::Date> dates) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  int n = dates.size();
  
  std::vector<bool> weekends(n);
  
  for (int i=0; i<n; i++) {
    weekends[i] = cal_obj.isWeekend(dates[i].weekday());
  }
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return weekends;
}

// [[Rcpp::export]]
std::vector<bool> cal_is_business_day_cpp(List cal, std::vector<QuantLib::Date> dates) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  int n = dates.size();
  
  std::vector<bool> business_days(n);
  
  for (int i=0; i<n; i++) {
    business_days[i] = cal_obj.isBusinessDay(dates[i]);
  }
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return business_days;
}

// [[Rcpp::export]]
std::vector<bool> cal_is_holiday_cpp(List cal, std::vector<QuantLib::Date> dates) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  int n = dates.size();
  
  std::vector<bool> holidays(n);
  
  for (int i=0; i<n; i++) {
    holidays[i] = cal_obj.isHoliday(dates[i]);
  }
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return holidays;
}

// [[Rcpp::export]]
std::vector<bool> cal_is_end_of_month_cpp(List cal, std::vector<QuantLib::Date> dates) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  int n = dates.size();
  
  std::vector<bool> end_of_month(n);
  
  for (int i=0; i<n; i++) {
    end_of_month[i] = cal_obj.isEndOfMonth(dates[i]);
  }
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return end_of_month;
}