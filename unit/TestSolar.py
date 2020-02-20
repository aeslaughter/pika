#!/usr/bin/env python
import datetime
from pysolar import solar, stime

"""
latitude_deg = 42.206 # positive in the northern hemisphere
longitude_deg = -71.382 # negative reckoning west from prime meridian in Greenwich, England
date = datetime.datetime(2007, 2, 18, 15, 13, 1, 130320, tzinfo=datetime.timezone.utc)
altitude_deg = solar.get_altitude(latitude_deg, longitude_deg, date)
q = solar.radiation.get_radiation_direct(date, altitude_deg)
"""

date = datetime.datetime(2007, 2, 18, 15, 13, 1, 130320, tzinfo=datetime.timezone.utc)

date = datetime.datetime(1980, 6, 24, tzinfo=datetime.timezone.utc)

jd = stime.get_julian_solar_day(date)


print(jd)
