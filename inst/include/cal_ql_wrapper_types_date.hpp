#ifndef _cal_ql_wrapper_types_date_h_
#define _cal_ql_wrapper_types_date_h_

// Include RcppCommon.h NOT Rcpp.h
#include <RcppCommon.h>

// Date types located here
#include "ql/time/date.hpp"
#include "ql/time/calendars/unitedstates.hpp"

// Definitions of all date-like conversions
namespace Rcpp {

  // Convert SEXP date -> ql date
  template <>
  QuantLib::Date as(SEXP date_sexp);

  // Convert ql date -> SEXP
  template <>
  SEXP wrap(const QuantLib::Date &ql_date);

  // Convert SEXP date vector -> vector of ql Date objects
  template <>
  std::vector<QuantLib::Date> as(SEXP date_vec_sexp);

  // Convert vector of ql Date objects -> SEXP date vector
  template <>
  SEXP wrap(const std::vector<QuantLib::Date> &ql_date_vec);
  
  template <> 
  QuantLib::UnitedStates::Market as(SEXP market_enum_val);

}

#endif