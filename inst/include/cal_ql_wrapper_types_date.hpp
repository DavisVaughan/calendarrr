// Here are the defintions of the types that get wrapped and as-ed
// Additionally, at the bottom are custom typdefs we want to use in the package

#ifndef cal_ql_wrapper_types_date_hpp
#define cal_ql_wrapper_types_date_hpp

// Date types located here
#include "ql/time/date.hpp"

// Include RcppCommon.h NOT Rcpp.h
#include <RcppCommon.h>

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

}

#endif