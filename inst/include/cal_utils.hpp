#ifndef cal_utils_hpp
#define cal_utils_hpp

#include <ql/time/businessdayconvention.hpp>
#include <ql/time/timeunit.hpp>

#include <Rcpp.h>

// Declare conversion functions that are used in other cpp files. They are
// implemented in cal_utils.cpp

QuantLib::BusinessDayConvention get_business_day_convention(const std::string &convention);

QuantLib::TimeUnit get_time_unit(const std::string &unit);

#endif