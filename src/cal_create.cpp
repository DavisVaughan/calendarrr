#include "ql/time/calendar.hpp"
#include "ql/time/calendars/all.hpp"
using namespace QuantLib;  

#include <Rcpp.h>
using namespace Rcpp;

// cal_create_calendar_cpp - just based on the way the Calendar API works,
// you can create multiple instances of the same calendar, but adding a holiday
// to one of them adds it to all of them from then on.

// [[Rcpp::export]]
SEXP cal_create_cpp(const std::string &cal) {

  // Init calendar pointer (must be a pointer for new and for Xptr)
  QuantLib::Calendar* cal_ptr = NULL;

  // Switch based on cal to create a calendar
  // We need to create "new" calendar objects so they are allocated on the 
  // heap. this way they don't go out of scope when they are passed to R
  if(cal == "TARGET") {
    cal_ptr = new QuantLib::TARGET();

  } else if (cal == "UnitedStates" || cal == "UnitedStates/Settlement") {
    cal_ptr = new QuantLib::UnitedStates(QuantLib::UnitedStates::Settlement);

  } else {
    throw std::invalid_argument("Calendar " + cal + " not recognised ");
  }

  // Pass back as XPtr
  Rcpp::XPtr<QuantLib::Calendar> cal_xptr(cal_ptr, true);
  return cal_xptr;
}