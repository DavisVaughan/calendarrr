#ifndef calendarrr_hpp
#define calendarrr_hpp

// This specifically named file gets included in RcppExports.cpp. 
// Why? Good question. We have custom wrapped and as-ed types for QuantLib
// Dates and they are return types / parameters to our exported cpp functions.
// This means they show up in RcppExports.cpp but need a header to go with them
// otherwise we get "Symbol not found" errors.
// So we include the wrap/as implementation header below.

#include "cal_quantlib_types_impl.hpp"

#endif