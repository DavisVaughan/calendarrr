#' @export
cal_add_holidays <- function(holidays) {
  cal <- cal_get_calendar()
  cal$add_holidays(holidays)
}

#' @export
cal_remove_holidays <- function(holidays) {
  cal <- cal_get_calendar()
  cal$remove_holidays(holidays)
}

#' @export
cal_get_holidays <- function(from, to, include_weekends = FALSE) {
  cal <- cal_get_calendar()
  cal$get_holidays(from, to, include_weekends)
}