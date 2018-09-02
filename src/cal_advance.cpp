#include <ql/types.hpp>
#include <ql/time/date.hpp>
#include <ql/time/calendar.hpp>
#include <ql/time/timeunit.hpp>
#include <ql/time/businessdayconvention.hpp>
using namespace QuantLib;  

#include "cal_quantlib_types.hpp"
#include "cal_creation.hpp"
#include "cal_utils.hpp"

#include <Rcpp.h>
using namespace Rcpp;

// There is also an advance() that works based off of a Period, but we
// don't need that as a Period = Integer + TimeUnit which is essentially 
// covered here

// [[Rcpp::export]]
std::vector<QuantLib::Date> cal_advance_cpp(List cal, 
                                            std::vector<QuantLib::Date> dates, 
                                            Rcpp::IntegerVector n,
                                            const std::string &unit,
                                            const std::string &convention,
                                            bool end_of_month = false) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  // Create BusinessDayConvention object
  QuantLib::BusinessDayConvention bdc = get_business_day_convention(convention);
  
  // Create TimeUnit
  QuantLib::TimeUnit time_unit = get_time_unit(unit);
  
  int n_dates = dates.size();
  
  std::vector<QuantLib::Date> advanced_dates(n_dates);
  
  for (int i = 0; i < n_dates; i++) {
    advanced_dates[i] = cal_obj.advance(dates[i], n[i], time_unit, bdc, end_of_month);
  }
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return advanced_dates;
}