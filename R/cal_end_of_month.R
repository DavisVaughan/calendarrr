#' @export
cal_end_of_month <- function(dates, cal = cal_create()) {
  validate_inherits(dates, "dates", "Date")
  cal_end_of_month_cpp(cal, dates)
}