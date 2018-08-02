#include <ql/time/calendar.hpp>
#include <ql/time/date.hpp>
using namespace QuantLib;  

#include "cal_creation.hpp"
#include "cal_quantlib_types.hpp"

#include <Rcpp.h>
using namespace Rcpp;

// we can return items of class std::vector<QuantLib::Date> because we have 
// a wrap() method for it, and because we have a calendarrr.h files that 
// includes the file containing the wrap method + the Quantlib namespace. 
// calendarrr.h is auto included in RcppExports.cpp, 
// so those QuantLib types are always defined

// [[Rcpp::export]]
std::vector<QuantLib::Date> cal_list_holidays_cpp(List cal, 
                                                  QuantLib::Date from, 
                                                  QuantLib::Date to, 
                                                  bool include_weekends) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  // Pull holidays
  std::vector<QuantLib::Date> holidays = QuantLib::Calendar::holidayList(cal_obj, from, to, include_weekends);
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return holidays;
}