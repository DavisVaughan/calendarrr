#include "cal_ql_wrapper_types_date.hpp"
#include "cal_creation.hpp"
#include "cal_utils.hpp"

using namespace QuantLib;  

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::vector<QuantLib::Date> cal_adjust_cpp(List cal, std::vector<QuantLib::Date> dates, const std::string &convention) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  // Create BusinessDayConvention object
  QuantLib::BusinessDayConvention bdc = get_business_day_convention(convention);
  
  int n = dates.size();
  
  std::vector<QuantLib::Date> adjusted_dates(n);
  
  for (int i=0; i < n; i++) {
    adjusted_dates[i] = cal_obj.adjust(dates[i], bdc);
  }
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return adjusted_dates;
}