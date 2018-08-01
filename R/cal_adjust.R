#' @export
cal_adjust <- function(dates, cal = cal_create(), convention = "following") {
  validate_inherits(dates, "dates", "Date")
  validate_inherits(convention, "convention", "character")
  
  cal_adjust_cpp(cal, dates, convention)
}