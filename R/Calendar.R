Calendar <- R6::R6Class("Calendar",
                        
  public = list(
    
    # Public variables
    cal = character(0),
    extra_holidays = NULL,
    
    # Initialize (called with new())
    initialize = function(cal = "TARGET") {
      
      # Force garbage collection to invoke finalizers
      gc(verbose = FALSE)
      
      # Doesn't work if the object is not assigned to anything
      if(is.null(private$instances$counter[[cal]])) {
        private$instances$counter[[cal]] <- 1L
      } else {
        stop(paste0("Cannot have more than 1 instance of ", cal), call. = FALSE)
      }
      
      self$cal <- cal
      private$pointer <- cal_create_cpp(cal)
    },
    
    reset_holidays = function() {
      if(!is.null(self$extra_holidays)) {
        cal_remove_holiday_cpp(private$pointer, self$extra_holidays)
      }
      invisible(self)
    },
    
    # Add a vector of holidays
    add_holidays = function(holidays) {
      stopifnot(inherits(holidays, "Date"))
      cal_add_holiday_cpp(private$pointer, holidays)
      self$extra_holidays <- c_dates(holidays, self$extra_holidays)
      invisible(self)
    },
    
    # Remove a vector of holidays
    remove_holidays = function(holidays) {
      stopifnot(inherits(holidays, "Date"))
      cal_remove_holiday_cpp(private$pointer, holidays)
      self$extra_holidays <- setdiff(self$extra_holidays, holidays)
      invisible(self)
    },
    
    # Retrieve all extra holidays
    get_holidays = function(from, to, include_weekends) {
      stopifnot(inherits(from, "Date"))
      stopifnot(inherits(to, "Date"))
      stopifnot(inherits(include_weekends, "logical"))
      cal_list_holidays_cpp(private$pointer, from, to, include_weekends)
    },
    
    is_weekend = function(dates) {
      stopifnot(inherits(dates, "Date"))
      cal_is_weekend_cpp(private$pointer, dates)
    },
    
    adjust = function(dates) {
      stopifnot(inherits(dates, "Date"))
      cal_adjust_cpp(private$pointer, dates)
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
      self$reset_holidays()
      private$instances$counter[[self$cal]] <- NULL
    }
  ),
  
  private = list(
    # External pointer to calendar C++ object
    pointer = NULL,
    # Shared number of instances
    instances = {
      inst <- new.env()
      inst$counter <- list()
      inst
    }
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