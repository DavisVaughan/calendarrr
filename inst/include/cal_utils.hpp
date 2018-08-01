#ifndef cal_utils_hpp
#define cal_utils_hpp

#include <ql/time/businessdayconvention.hpp>
#include <ql/time/timeunit.hpp>

#include <Rcpp.h>

QuantLib::BusinessDayConvention get_business_day_convention(const std::string &convention);

QuantLib::TimeUnit get_time_unit(const std::string &unit);

#endif