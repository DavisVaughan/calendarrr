#ifndef cal_create_h
#define cal_create_h

#include <ql/time/calendar.hpp>
#include <ql/time/date.hpp>

// Required because this get's moved into calendarrr.h
#include "cal_ql_wrapper_types_date.hpp"

#include <Rcpp.h>
using namespace Rcpp;

// Calendar creation functions used in other cpp files for setup and teardown
// of calendars

QuantLib::Calendar cal_create_cpp(List cal);

void cal_add_holiday_cpp(QuantLib::Calendar cal, std::vector<QuantLib::Date> holidays);

void cal_remove_holiday_cpp(QuantLib::Calendar cal, std::vector<QuantLib::Date> holidays);
  
#endif