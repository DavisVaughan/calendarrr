#include <ql/time/calendar.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/date.hpp>
using namespace QuantLib;  

#include "cal_creation.hpp"

#include <Rcpp.h>
using namespace Rcpp;

// cal_create_calendar_cpp - just based on the way the Calendar API works,
// you can create multiple instances of the same calendar, but adding a holiday
// to one of them adds it to all of them from then on.

QuantLib::Calendar cal_create_cpp(List cal) {

  // Check calendar class
  if(!cal.inherits("calendar")) stop("`cal` must be a `calendar` object.");
  
  // Extract elements
  std::string cal_name = as<std::string>(cal["name"]);
  std::vector<QuantLib::Date> extra_holidays = as< std::vector<QuantLib::Date> >(cal["extra_holidays"]);
  
  // Init calendar pointer (must be a pointer for new and for Xptr)
  QuantLib::Calendar cal_obj;
  QuantLib::Calendar cal_obj_with_holidays;

  // Switch based on cal to create a calendar
  // We need to create "new" calendar objects so they are allocated on the 
  // heap. this way they don't go out of scope when they are passed to R
  if(cal_name == "TARGET") {
    cal_obj = QuantLib::TARGET();

  } else if (cal_name == "UnitedStates" || cal_name == "UnitedStates/Settlement") {
    cal_obj = QuantLib::UnitedStates(QuantLib::UnitedStates::Settlement);

  } else {
    throw std::invalid_argument("Calendar " + cal_name + " not recognised ");
  }
  
  cal_add_holiday_cpp(cal_obj, extra_holidays);

  return cal_obj;
}


// Holidays can be added and removed, but once a holiday is added it is 
// persistent across all instances of a specific calendar!

// Holidays can only be added on non-weekend days

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