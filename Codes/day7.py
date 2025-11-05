import calendar

def get_day(day: str, n: int) -> str:
    """
    day: should be one of "sun", "mon", ...
    n: can be any integer.
    """
    if not isinstance(n, int):
        raise ValueError("Please enter an integer n.")
    if n == 0:
        return day
    days = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]
    if day not in days:
        raise ValueError("Please enter valid day name like sun, mon, ....")
    
    i = days.index(day)
    return days[(i + n) % 7]

# print(get_day("Wed", 50))

def get_sundays_in_year(first_day: str, year: int):
    """
    first_day: weekday name of Jan 1 of `year` (one of "Sun","Mon",...,"Sat")
    year: integer year
    Returns: (num_months_with_first_day_sunday, weekday_name_of_Jan1_next_year)
    """
    days = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]
    if first_day not in days:
        raise ValueError("Please enter valid day name (Sun, Mon, ...).")
    if not isinstance(year, int):
        raise ValueError("Please enter integer year.")
    # days in month indexed 1..12
    num_days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    if calendar.isleap(year):
        num_days[2] = 29

    first_index = days.index(first_day)
    cum_days = 0
    count = 0

    for m in range(1, 13):
        weekday_of_first = (first_index + cum_days) % 7
        if days[weekday_of_first] == "Sun":
            count += 1
        cum_days += num_days[m]
    
    next_year_first = days[(first_index + cum_days) % 7]
    return count, next_year_first

def solution():
    first_day = "Wed" # 1 Jan 1901 was Wednesday.
    total = 0

    for year in range(1901, 2001):
        sunday_count, next_year_first = get_sundays_in_year(first_day, year)
        total += sunday_count
        first_day = next_year_first
    
    return total

# print(get_sundays_in_year("Mon", 1900))
print(solution())