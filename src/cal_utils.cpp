#include <ql/time/businessdayconvention.hpp>
#include <ql/time/timeunit.hpp>

#include "cal_utils.hpp"

#include <Rcpp.h>
using namespace Rcpp;

QuantLib::BusinessDayConvention get_business_day_convention(const std::string &convention) {
  
  if (convention == "following")
    return QuantLib::Following;
  
  else if (convention == "modified following")
    return QuantLib::ModifiedFollowing;
  
  else if (convention == "preceding")
    return QuantLib::Preceding;
  
  else if (convention == "modified preceding")
    return QuantLib::ModifiedPreceding;
  
  else if (convention == "unadjusted")
    return QuantLib::Unadjusted;
  
  else if (convention == "half month modified following")
    return QuantLib::HalfMonthModifiedFollowing;
  
  else if (convention == "nearest")
    return QuantLib::Nearest;
  
  else
    warning("Unknown `convention`, defaulting to 'unadjusted'.");
    return QuantLib::Unadjusted;
}


QuantLib::TimeUnit get_time_unit(const std::string &unit) {
  
  if (unit == "days")
    return QuantLib::Days;
  
  else if (unit == "weeks")
    return QuantLib::Weeks;
  
  else if (unit == "months")
    return QuantLib::Months;
  
  else if (unit == "years")
    return QuantLib::Years;
  
  else
    warning("Unknown `unit`, defaulting to 'Days'.");
  
  return QuantLib::Days;
}