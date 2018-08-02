#ifndef cal_quantlib_types_impl_hpp
#define cal_quantlib_types_impl_hpp

#include <ql/time/calendar.hpp>

#include "cal_quantlib_types.hpp"

#include <Rcpp.h>
using namespace Rcpp;

// Implementations of all date-like conversions
namespace Rcpp {

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
  template <> 
  SEXP wrap(const std::vector<QuantLib::Date> &ql_date_vec) {
    
    int n = ql_date_vec.size();
    Rcpp::DateVector date_vec(n);
    
    for (int i = 0; i<n; i++) {
      
      // QL::BigInteger can cast to double
      double date_double = static_cast<double>(ql_date_vec[i].serialNumber()); 
      
      date_vec[i] = Rcpp::Date(date_double - ql_to_jan_1970_offset);
      
    }
    
    return Rcpp::wrap(date_vec);
  }

}


#endif