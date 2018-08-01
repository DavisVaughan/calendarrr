
<!-- README.md is generated from README.Rmd. Please edit that file -->

# calendarrr

The goal of `calendarrr` is to enhance the current ecosystem of date
manipulation packages out there, mainly `lubridate`, by adding date
calculation methods that respect customizable business days and
holidays.

`calendarrr` provides an R frontend to the `QuantLib` *Calendar*
library. This package shamelessly rips out sections of `QuantLib`
corresponding to calendar calculations, and exposes them as the S3
class, `calendar`.

## Related work

The `RQuantLib` package exposes some of this as well, but in a different
form and as a subset of a larger purpose of exposing the entire
`QuantLib` library. There are a few benefits of `calendarrr` vs
`RQuantLib`.

  - `RQuantLib` does not have the ability to add custom holidays.
  - `RQuantLib` requires that you install `QuantLib` yourself (at least
    on Mac), which can be a major pain and raise the barrier to entry
    significantly. `calendarrr` is self-contained.
  - `calendarrr` tries to focus on providing a consistent and user
    friendly interface to the calendar library.

## Installation

You can install the released version of calendarrr from
[CRAN](https://CRAN.R-project.org) with:

``` r
# no you cannot
install.packages("calendarrr")
```

And the development version from [GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("DavisVaughan/calendarrr")
```

## Example

Easily create a calendar with `cal_create()`. Provide it the name of the
QuantLib calendar you want to create. There are ~30 calendars, each with
their own unique holiday schedule (not all implemented yet).

Use `cal_add_holidays()` to add custom holidays on top of the holidays
already <!-- implemented in your selected calendar. -->

``` r
library(calendarrr)
library(magrittr)

# some random days to add as extra holidays
extra_holidays <- as.Date(c("2018-01-02", "2018-01-04"))

usa <- cal_create("UnitedStates") %>%
  cal_add_holidays(extra_holidays)

usa
#> <Calendar:UnitedStates>
#> Extra holidays:
#>    - 2018-01-02
#>    - 2018-01-04
```

You can check if a certain date is a holiday, weekend, business day, or
the end of the month.

``` r
# A Tuesday
today <- as.Date("2018-07-31")
custom_holiday <- as.Date("2018-01-02")

cal_is_business_day(dates = today, cal = usa)
#> [1] TRUE

cal_is_end_of_month(today, usa)
#> [1] TRUE

cal_is_holiday(today, usa)
#> [1] FALSE

cal_is_holiday(custom_holiday, usa)
#> [1] TRUE

cal_is_weekend(today, usa)
#> [1] FALSE
```

You can “adjust” a date relative to a calendar and a business day
convention. Adjusting moves a date to the next/previous business day if
it is not already a business day.

``` r
a_saturday <- as.Date("2018-07-28")

# Adjusts to next monday
cal_adjust(a_saturday, usa, convention = "following")
#> [1] "2018-07-30"

# Adjusts to previous friday
cal_adjust(a_saturday, usa, convention = "preceding")
#> [1] "2018-07-27"
```

You can “advance” a date relative to a calendar and business day
convention. Advancing moves a date by a `length` + `unit` to the next
business day. For example, `1 day`.

``` r
# Shift 5 business days forward
# (1 business week in this case because there were no holidays)
cal_advance(today, usa, n = 5, unit = "days")
#> [1] "2018-08-07"

# What if this was around a holiday? Say, July 4th?
# July 4th was a Wednesday
july_4 <- as.Date("2018-07-04")
july_2_monday <- july_4 - 2

# Moves forward 5 business days, ignoring July 4th
cal_advance(july_2_monday, usa, n = 5, unit = "days")
#> [1] "2018-07-10"

# You can go backwards too
cal_advance(july_2_monday, usa, n = -5, unit = "days")
#> [1] "2018-06-25"

# Also, note that the default calendar does not include July 4th as a holiday,
# but the UnitedStates one does. Here is the default:
cal_advance(july_2_monday, n = 5, unit = "days")
#> [1] "2018-07-09"
```

There is also a handy `cal_end_of_month()` function.

``` r
cal_end_of_month(as.Date("2018-01-15"), usa)
#> [1] "2018-01-31"
```

All functions are vectorized, of course, and are blazing fast because
they are written in C++.

``` r
lub_end_of_month <- function(x) {
  d <- lubridate::days_in_month(x)
  m <- lubridate::month(x)
  y <- lubridate::year(x)
  lubridate::make_date(y, m, d)
}

dates <- as.Date("2018-01-01") + 1:1000

microbenchmark::microbenchmark(
  cal_end_of_month(dates, usa),
  lub_end_of_month(dates)
)
#> Unit: microseconds
#>                          expr      min        lq      mean    median
#>  cal_end_of_month(dates, usa)  163.334  179.8795  205.3536  189.6625
#>       lub_end_of_month(dates) 1074.118 1204.3595 3248.6423 1263.8750
#>         uq        max neval
#>   203.1485   1007.464   100
#>  1488.0445 132263.262   100
```

Also note that the results of these are not equivalent, as
`cal_end_of_month()` again respects business days and will not allow the
end of the month to fall on a business day or holiday. For example,
`2018-03-31` is a
Saturday.

``` r
# Respects business day and says the "end of month" is the last business day
# in March
cal_end_of_month(dates, usa)[59]
#> [1] "2018-03-30"

# Just goes to the end of the month
lub_end_of_month(dates)[59]
#> [1] "2018-03-31"
```
