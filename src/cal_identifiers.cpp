#include "cal_ql_wrapper_types_date.hpp"
using namespace QuantLib;  

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::vector<bool> cal_is_weekend_cpp(SEXP cal_sexp, std::vector<QuantLib::Date> dates) {
  
  // Retrieve the R pointer to the calendar
  XPtrToCalendar cal_xptr(cal_sexp);
  
  int n = dates.size();
  
  std::vector<bool> weekends(n);
  
  for (int i=0; i<n; i++) {
    weekends[i] = cal_xptr->isWeekend(dates[i].weekday());
  }
  
  return weekends;
}

// [[Rcpp::export]]
std::vector<QuantLib::Date> cal_adjust_cpp(SEXP cal_sexp, std::vector<QuantLib::Date> dates) {
  
  // STILL NEED adjust() CONVENTION
  
  // Retrieve the R pointer to the calendar
  XPtrToCalendar cal_xptr(cal_sexp);
  
  int n = dates.size();
  
  std::vector<QuantLib::Date> adjusted_dates(n);
  
  for (int i=0; i < n; i++) {
    adjusted_dates[i] = cal_xptr->adjust(dates[i]);
  }
  
  return adjusted_dates;
}