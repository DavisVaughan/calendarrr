#' @export
cal_is_weekend <- function(dates, cal = cal_create()) {
  validate_inherits(dates, "dates", "Date")
  cal_is_weekend_cpp(cal, dates)
}

#' @export
cal_is_business_day <- function(dates, cal = cal_create()) {
  validate_inherits(dates, "dates", "Date")
  cal_is_business_day_cpp(cal, dates)
}

#' @export
cal_is_holiday <- function(dates, cal = cal_create()) {
  validate_inherits(dates, "dates", "Date")
  
  # Note that a "holiday" = !is_business_day()
  # so weekends show up. use (is_holiday() & !is_weekend())
  # to get _only_ business day holidays
  cal_is_holiday_cpp(cal, dates) & !cal_is_weekend(dates, cal)
}

#' @export
cal_is_holiday_or_weekend <- function(dates, cal = cal_create()) {
  validate_inherits(dates, "dates", "Date")
  
  # This is the default QuantLib behavior so we include it
  cal_is_holiday_cpp(cal, dates)
}

#' @export
cal_is_end_of_month <- function(dates, cal = cal_create()) {
  validate_inherits(dates, "dates", "Date")
  cal_is_end_of_month_cpp(cal, dates)
}