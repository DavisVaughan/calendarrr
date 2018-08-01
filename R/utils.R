c_dates <- function(...) {
  as_date(c(...))
}

setdiff_dates <- function(x, y) {
  as_date(setdiff(x, y))
}

as_date <- function(x) {
  as.Date(x, origin = "1970-01-01")
}

get_extra_holidays <- function(cal) {
  cal[["extra_holidays"]]
}

set_extra_holidays <- function(cal, holidays) {
  stopifnot(inherits(holidays, "Date"))
  cal[["extra_holidays"]] <- holidays
  cal
}

get_name <- function(cal) {
  cal[["name"]]
}

empty_date <- function() {
  empty_numeric <- numeric()
  class(empty_numeric) <- "Date"
  empty_numeric
}
