#' @export
cal_create <- function(name = "TARGET") {
  
  validate_inherits(name, "name", "character")
  validate_calendar_name(name)
  
  new_calendar(name, extra_holidays = empty_date())
}

new_calendar <- function(name, extra_holidays, ..., subclass = NULL) {
  stopifnot(is.character(name))
  stopifnot(inherits(extra_holidays, c("Date", "NULL")))
  
  structure(
    list(
      name = name, 
      extra_holidays = extra_holidays
    ), 
    class = c(subclass, "calendar")
  )
}