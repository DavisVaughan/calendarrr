#' @export
cal_create <- function(name = "TARGET") {
  cal <- Calendar$new(cal = name)
  cal
}