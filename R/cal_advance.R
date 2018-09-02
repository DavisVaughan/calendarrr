# TODO) Document that we allow dates and n to be vectors. Should unit and convention
# be vectors as well?

#' @export
cal_advance <- function(dates, 
                        cal = cal_create(), 
                        n = 1L, 
                        unit = "days", 
                        convention = "following", 
                        end_of_month = FALSE) {
  
  validate_inherits(dates, "dates", "Date")
  validate_inherits(unit, "unit", "character")
  validate_inherits(convention, "convention", "character")
  validate_inherits(end_of_month, "end_of_month", "logical")
  
  n <- as_integer(n)
  
  recycle_n <- max(length(dates), length(n))
  dates <- recycle(dates, recycle_n)
  n <- recycle(n, recycle_n)
  
  cal_advance_cpp(cal, dates, n, unit, convention, end_of_month)
}

as_integer <- function(x) {
  if(is.integer(x)) {
    x
  } else {
    as.integer(x)
  }
}