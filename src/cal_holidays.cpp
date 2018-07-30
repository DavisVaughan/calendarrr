#include "ql/time/calendar.hpp"
#include "ql/time/date.hpp"
#include "cal_ql_wrapper_types_date_impl.hpp"
using namespace QuantLib;  

#include <Rcpp.h>
using namespace Rcpp;

// Holidays can be added and removed, but once a holiday is added it is 
// persistent across all instances of a specific calendar!

// Holidays can only be added on non-weekend days

// [[Rcpp::export]]
SEXP cal_add_holiday_cpp(SEXP cal_sexp, std::vector<QuantLib::Date> holidays) {
  
  // Retrieve the R pointer to the calendar
  XPtrToCalendar cal_xptr(cal_sexp);
  
  // Init looping vars
  QuantLib::Date holiday;
  int n = holidays.size();
  
  // Add holidays
  for(int i = 0; i < n; i++) {
    holiday = holidays[i];
    cal_xptr->addHoliday(holiday);
  }

  return cal_xptr;
}

// [[Rcpp::export]]
SEXP cal_remove_holiday_cpp(SEXP cal_sexp, std::vector<QuantLib::Date> holidays) {
  
  // Retrieve the R pointer to the calendar
  XPtrToCalendar cal_xptr(cal_sexp);
  
  // Init looping vars
  QuantLib::Date holiday;
  int n = holidays.size();
  
  // Remove holidays
  for(int i = 0; i < n; i++) {
    holiday = holidays[i];
    cal_xptr->removeHoliday(holiday);
  }
  
  return cal_xptr;
}

// we can return items of class std::vector<QuantLib::Date> because we have 
// a wrap() method for it, and because we have a calendarrr.h files that 
// includes the file containing the wrap method + the Quantlib namespace. 
// calendarrr.h is auto included in RcppExports.cpp, 
// so those QuantLib types are always defined

// [[Rcpp::export]]
std::vector<QuantLib::Date> cal_list_holidays_cpp(SEXP cal_sexp, 
                                                  QuantLib::Date from, 
                                                  QuantLib::Date to, 
                                                  bool include_weekends) {
  
  Rcpp::XPtr<QuantLib::Calendar> cal_xptr(cal_sexp);
  std::vector<QuantLib::Date> holidays = QuantLib::Calendar::holidayList(*cal_xptr, from, to, include_weekends);
  
  return holidays;
}