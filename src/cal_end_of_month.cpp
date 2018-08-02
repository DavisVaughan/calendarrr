#include <ql/time/date.hpp>
#include <ql/time/calendar.hpp>
using namespace QuantLib;

#include "cal_quantlib_types.hpp"
#include "cal_creation.hpp"

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::vector<QuantLib::Date> cal_end_of_month_cpp(List cal, 
                                                 std::vector<QuantLib::Date> dates) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  int n = dates.size();
  
  std::vector<QuantLib::Date> end_of_month_dates(n);
  
  for (int i=0; i<n; i++) {
    end_of_month_dates[i] = cal_obj.endOfMonth(dates[i]);
  }
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return end_of_month_dates;
}