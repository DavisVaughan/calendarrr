#ifndef _cal_ql_wrapper_types_date_impl_h_
#define _cal_ql_wrapper_types_date_impl_h_

#include "cal_ql_wrapper_types_date.hpp"
#include <ql/time/calendar.hpp>

#include <Rcpp.h>
using namespace Rcpp;

// Implementations of all date-like conversions
namespace Rcpp {

  typedef Rcpp::XPtr<QuantLib::Calendar> XPtrToCalendar;

  // Offset to R / Unix epoch 
  static const unsigned int ql_to_jan_1970_offset = 25569;
  
  // Convert SEXP date -> Rcpp Date -> int -> ql date
  template <> 
  QuantLib::Date as(SEXP date_sexp) {
    
    Rcpp::Date dt(date_sexp);
    return QuantLib::Date(static_cast<int>(dt.getDate()) + ql_to_jan_1970_offset);
    
  }
  
  // Convert ql date -> BigInteger -> double -> Rcpp Date -> SEXP
  template <> 
  SEXP wrap(const QuantLib::Date &d) {
    
    // QL::BigInteger can cast to double
    double dt = static_cast<double>(d.serialNumber());
    return Rcpp::wrap(Rcpp::Date(dt - ql_to_jan_1970_offset));
    
  }
  
  // Convert SEXP date vec -> Rcpp date vector -> each element coerced to ql date -> stored in vector container
  template <> 
  std::vector<QuantLib::Date> as(SEXP date_vec_sexp) {
    
    // SEXP date vec -> Rcpp date vector
    Rcpp::DateVector date_vec(date_vec_sexp);
    int n = date_vec.size();
    
    // Initialize ql date vector
    std::vector<QuantLib::Date> ql_date_vec(n);
    
    // Fill the ql date vector using the same method as single Date
    for (int i = 0; i < n; i++) {
      
  #if RCPP_VERSION >= Rcpp_Version(0,12,8)
      ql_date_vec[i] = QuantLib::Date(static_cast<int>(Rcpp::Date(date_vec[i]).getDate()) + ql_to_jan_1970_offset);
  #else            
      ql_date_vec[i] = QuantLib::Date(static_cast<int>(date_vec[i].getDate()) + ql_to_jan_1970_offset);
  #endif    
      
    }
    
    return ql_date_vec;
    
  }
  
  // non-intrusive extension via template specialisation
  template <> SEXP wrap(const std::vector<QuantLib::Date> &dvec) {
    int n = dvec.size();
    Rcpp::DateVector dtvec(n);
    for (int i = 0; i<n; i++) {
      // QL::BigInteger can cast to double
      double dt = static_cast<double>(dvec[i].serialNumber()); 
      dtvec[i] = Rcpp::Date(dt - ql_to_jan_1970_offset);
    }
    return Rcpp::wrap(dtvec);
  }
  
  // As an Integer from R to a UnitedStates Market enum value
  template <>
  QuantLib::UnitedStates::Market as(SEXP market_enum_val) {
    int market_enum_int = Rcpp::as<int>(market_enum_val);
    QuantLib::UnitedStates::Market ql_market_enum = static_cast<QuantLib::UnitedStates::Market>(market_enum_int);
    return ql_market_enum;
  }

}


#endif