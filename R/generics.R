print.calendar <- function(x, ...) {
  
    extra_holidays <- get_extra_holidays(x)

    # Extra holidays
    if(length(extra_holidays) > 0) {
      cat_holidays <- paste0("   - ", extra_holidays[order(extra_holidays)], "\n")
    } else {
      cat_holidays <- paste0("   - None", "\n")
    }

    # Print
    cat("<Calendar:", get_name(x), ">", "\n",
        "Extra holidays:", "\n",
        cat_holidays,
        sep = "")
}