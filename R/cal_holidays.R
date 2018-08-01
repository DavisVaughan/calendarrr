#' @export
cal_add_holidays <- function(cal, holidays) {
  stopifnot(inherits(holidays, "Date"))
  
  all_extra_holidays <- c_dates(holidays, get_extra_holidays(cal))
  
  # Should not be able to add the same holiday twice
  all_unique_extra_holidays <- unique(all_extra_holidays)
  
  cal <- set_extra_holidays(cal, all_unique_extra_holidays)
  
  cal
}

#' @export
cal_remove_holidays <- function(cal, holidays) {
  stopifnot(inherits(holidays, "Date"))
  
  extra_holidays_to_keep <- setdiff_dates(get_extra_holidays(cal), holidays)
  
  cal <- set_extra_holidays(cal, extra_holidays_to_keep)
  
  cal
}

#' @export
cal_get_holidays <- function(from, to, cal = cal_create(), include_weekends = FALSE) {
  stopifnot(inherits(from, "Date"))
  stopifnot(inherits(to, "Date"))
  stopifnot(inherits(include_weekends, "logical"))
  
  cal_list_holidays_cpp(cal, from, to, include_weekends)
}
