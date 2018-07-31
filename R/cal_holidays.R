#' @export
cal_add_holidays <- function(cal, holidays) {
  cal$add_holidays(holidays)
  cal
}

#' @export
cal_remove_holidays <- function(cal, holidays) {
  cal$remove_holidays(holidays)
  cal
}

#' @export
cal_get_holidays <- function(cal, from, to, include_weekends = FALSE) {
  cal$get_holidays(from, to, include_weekends)
}