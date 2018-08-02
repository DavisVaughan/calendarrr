#ifndef calendarrr_hpp
#define calendarrr_hpp

// This specifically named file gets included in RcppExports.cpp so 
// types there can refer to custom wrap/as functions    

// We have to include the actual implementation header otherwise we get
// "Symbol not found" errors
#include "cal_quantlib_types_impl.hpp"
#include "cal_utils.hpp"

#endif