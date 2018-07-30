Calendar <- R6::R6Class("Calendar",
                        
  public = list(
    
    # Public variables
    cal = character(0),
    extra_holidays = NULL,
    
    # Initialize (called with new())
    initialize = function(cal = "TARGET") {
      self$cal <- cal
      private$pointer <- cal_create_cpp(cal)
    },
    
    # Add a vector of holidays
    add_holidays = function(holidays) {
      stopifnot(inherits(holidays, "Date"))
      cal_add_holiday_cpp(private$pointer, holidays)
      self$extra_holidays <- c_dates(holidays, self$extra_holidays)
    },
    
    # Remove a vector of holidays
    remove_holidays = function(holidays) {
      stopifnot(inherits(holidays, "Date"))
      cal_remove_holiday_cpp(private$pointer, holidays)
      self$extra_holidays <- setdiff(self$extra_holidays, holidays)
    },
    
    # Retrieve all extra holidays
    get_holidays = function(from, to, include_weekends) {
      stopifnot(inherits(from, "Date"))
      stopifnot(inherits(to, "Date"))
      stopifnot(inherits(include_weekends, "logical"))
      cal_list_holidays_cpp(private$pointer, from, to, include_weekends)
    },
    
    # Custom print method
    print = function(...) {
      
      extra_holidays <- self$extra_holidays
      
      # Extra holidays
      if(length(extra_holidays) > 0) {
        cat_holidays <- paste0("   - ", extra_holidays[order(extra_holidays)], "\n")
      } else {
        cat_holidays <- paste0("   - None", "\n")
      }
      
      # Print
      cat("<Calendar:", self$cal, ">", "\n",
          "Extra holidays:", "\n",
          cat_holidays,
          sep = "")
    },
    
    # Since all instances of a specific calendar share holidays, 
    # remove holidays when this one goes out of R scope and R runs the gc()
    # It doesn't happen that often so it's not reliable unless the user
    # runs gc() themselves.
    finalize = function() {
      if(!is.null(self$extra_holidays)) {
        cal_remove_holiday_cpp(private$pointer, self$extra_holidays)
      }
    }
  ),
  
  private = list(
    pointer = NULL
  )
)

c_dates <- function(...) {
  as_date(c(...))
}

setdiff_dates <- function(x, y) {
  as_date(setdiff(x, y))
}

as_date <- function(x) {
  as.Date(x, origin = "1970-01-01")
}