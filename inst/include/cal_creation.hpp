#ifndef cal_create_h
#define cal_create_h

#include <ql/time/calendar.hpp>
#include <ql/time/date.hpp>

#include <Rcpp.h>
using namespace Rcpp;

// We need to know how to setup and reset Calendar objects in our other cpp
// files. We need to include cal_add_holiday_cpp() as well because it is in
// cal_create_cpp()

QuantLib::Calendar cal_create_cpp(List cal);

void cal_add_holiday_cpp(QuantLib::Calendar cal, std::vector<QuantLib::Date> holidays);

void cal_remove_holiday_cpp(QuantLib::Calendar cal, std::vector<QuantLib::Date> holidays);
  
#endif