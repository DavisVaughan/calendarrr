#include "cal_quantlib_types.hpp"
#include "cal_creation.hpp"

using namespace QuantLib;

#include <Rcpp.h>
using namespace Rcpp;

#include <boost/cstdint.hpp>

// [[Rcpp::export]]
std::vector<boost::int32_t> cal_business_days_between_cpp(List cal, 
                                             std::vector<QuantLib::Date> from, 
                                             std::vector<QuantLib::Date> to, 
                                             bool include_first = true, 
                                             bool include_last = false) {
  
  // Create with holidays
  QuantLib::Calendar cal_obj = cal_create_cpp(cal);
  
  int n_from = from.size();
  int n_to = to.size();
  
  if(n_from != n_to) {
    stop("`from` and `to` must be the same length.");
  }
  
  std::vector<boost::int32_t> days_between(n_from);
  
  for (int i=0; i < n_from; i++) {
    days_between[i] = cal_obj.businessDaysBetween(from[i], to[i], include_first, include_last);
  }
  
  // Reset
  cal_remove_holiday_cpp(cal_obj, cal["extra_holidays"]);
  
  return days_between;
}