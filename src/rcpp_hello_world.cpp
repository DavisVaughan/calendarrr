#include "ql/time/date.hpp"
#include "ql/types.hpp"
#include "ql/time/calendar.hpp"
#include "ql/time/calendars/all.hpp"
using namespace QuantLib;

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector rcpp_hello_world() {
  
    QuantLib::Period x = QuantLib::Period(1, Years);
    
    // These are really just special doubles
    QuantLib::Real y = years(x);
    
    // QuantLib dates
    QuantLib::Day d = 1;
    QuantLib::Month m = QuantLib::Feb;
    QuantLib::Year yr = 1990;
    
    QuantLib::Date dte = QuantLib::Date(d, m, yr);
    
    // Real -> double -> SEXP -> NumericVector
    // QuantLib::Real x_real = 4;
    // SEXP x_sexp = Rcpp::wrap<Real, double>(x_real);
    // NumericVector x_double = Rcpp::as<NumericVector>(x_sexp);
    
    // But you can already go straight to NumericVector...
    //NumericVector x_straight = NumericVector::create(x_real);

    NumericVector x_double(1);
    
    // promote to Market enum
    QuantLib::UnitedStates::Market us_enum = static_cast<QuantLib::UnitedStates::Market>(0);
    
    return x_double;
}
