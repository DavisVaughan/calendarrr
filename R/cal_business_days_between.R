#' @export
cal_business_days_between <- function(from, to, cal = cal_create(), include_first = TRUE, include_last = FALSE) {
  validate_inherits(from, "dates", "Date")
  validate_inherits(to, "dates", "Date")
  validate_inherits(include_first, "include_first", "logical")
  validate_inherits(include_last, "include_last", "logical")
  
  cal_business_days_between_cpp(cal, from, to, include_first, include_last)
}