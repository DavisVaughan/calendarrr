#' @useDynLib calendarrr, .registration=TRUE
#' @import Rcpp
#' @import methods
NULL

# Set up global pkg environment for current calendar
.calendarrr <- new.env()
.calendarrr$cal <- NULL