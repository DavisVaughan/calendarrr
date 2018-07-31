#' #' @export
#' cal_set_calendar <- function(cal) {
#'   .calendarrr$cal <- Calendar$new(cal = cal)
#'   cat("Calendar set to:", cal, "\n")
#'   # Ensure the previous calendar is cleaned up by the finalizer
#'   gc_mat <- gc(verbose = FALSE)
#'   rm(gc_mat)
#' }
#' 
#' #' @export
#' cal_get_calendar <- function() {
#'   
#'   # Set to default
#'   if(is.null(.calendarrr$cal)) {
#'     cal_set_calendar("TARGET")
#'   }
#'   
#'   .calendarrr$cal
#' }
