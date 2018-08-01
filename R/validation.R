validate_inherits <- function(x, x_nm, what) {
  if(!inherits(x, what)) {
    x_what <- glue::glue_collapse(what, ", ", last = ", or ")
    msg <- glue::glue("`{x_nm}` must be a {x_what}.")
    stop(msg, call. = FALSE)
  }
}

validate_calendar_name <- function(x) {
  is_valid <- x %in% cal_get_calendars()
  
  if(!is_valid) {
    msg <- glue::glue("`{x}` must be a calendar name in `cal_get_calendars()`.")
    stop(msg, call. = FALSE)
  }
}