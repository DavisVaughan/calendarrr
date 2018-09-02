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

# This recycling does not allow for multiples (2 becomes 4 kind of thing)
# It only recycles length 1 to length n, or does nothing if n_x == n already
recycle <- function(x, n) {
  x_n <- length(x)
  
  valid_length <- (x_n == 1L) | (x_n == n) 
  
  if(!valid_length) {
    stop(
      "Object to be recycled is length ", 
      x_n, 
      " but should be length 1 or ", 
      n, 
      ".",
      call. = FALSE
    )
  }
  
  # length 1, recycle
  if(x_n == 1L) {
    x <- rep(x, times = n)
  }
  
  x
}
