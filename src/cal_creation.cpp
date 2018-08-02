#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/date.hpp>
using namespace QuantLib;  

#include "cal_creation.hpp"
#include "cal_quantlib_types.hpp"

#include <Rcpp.h>
using namespace Rcpp;

// Retrieve a QuantLib::Calendar based on the calendar string name

QuantLib::Calendar get_calendar_instance(std::string cal_name) {
  
  // Switch based on cal_name to create a calendar
  
  if(cal_name == "TARGET") {
    return(QuantLib::TARGET());
    
  } else if (cal_name == "UnitedStates" || cal_name == "UnitedStates/Settlement") {
    return(QuantLib::UnitedStates(QuantLib::UnitedStates::Settlement));
    
  } else {
    // Throw an R error
    std::string msg = "Calendar `" + cal_name + "` not recognised ";
    ::Rf_error(msg.c_str());
  }
  
}

// cal_create_calendar_cpp - just based on the way the Calendar API works,
// you can create multiple instances of the same calendar, but adding a holiday
// to one of them adds it to all of them from then on.

QuantLib::Calendar cal_create_cpp(List cal) {

  // Check calendar class
  if(!cal.inherits("calendar")) stop("`cal` must be a `calendar` object.");
  
  // Extract elements
  std::string cal_name = as<std::string>(cal["name"]);
  std::vector<QuantLib::Date> extra_holidays = as< std::vector<QuantLib::Date> >(cal["extra_holidays"]);
  
  // Init calendar
  QuantLib::Calendar cal_obj = get_calendar_instance(cal_name);
  
  cal_add_holiday_cpp(cal_obj, extra_holidays);

  return cal_obj;
}

// Holidays can be added and removed, but once a holiday is added it is 
// persistent across all instances of a specific calendar!

// This is one of the reasons we do not return an external pointer to R.
// We want to create a fresh calendar each time, and add and remove extra
// holidays as necessary.

// Holidays can only be added on non-weekend days.

// These functions are NOT exported. Their R counterparts just add to the list
// element, "extra_holidays", of the calendar instance.

void cal_add_holiday_cpp(QuantLib::Calendar cal, std::vector<QuantLib::Date> holidays) {
  
  // Init looping vars
  QuantLib::Date holiday;
  int n = holidays.size();
  
  // Add holidays
  for(int i = 0; i < n; i++) {
    holiday = holidays[i];
    cal.addHoliday(holiday);
  }

}


void cal_remove_holiday_cpp(QuantLib::Calendar cal, std::vector<QuantLib::Date> holidays) {
  
  // Init looping vars
  QuantLib::Date holiday;
  int n = holidays.size();
  
  // Remove holidays
  for(int i = 0; i < n; i++) {
    holiday = holidays[i];
    cal.removeHoliday(holiday);
  }
  
}