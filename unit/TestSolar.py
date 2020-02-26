#!/usr/bin/env python
import datetime
import math
from pysolar import solar, stime, constants

"""
latitude_deg = 42.206 # positive in the northern hemisphere
longitude_deg = -71.382 # negative reckoning west from prime meridian in Greenwich, England
date = datetime.datetime(2007, 2, 18, 15, 13, 1, 130320, tzinfo=datetime.timezone.utc)
altitude_deg = solar.get_altitude(latitude_deg, longitude_deg, date)
q = solar.radiation.get_radiation_direct(date, altitude_deg)
"""

print("TEST(solar, julian_day)")
date = datetime.datetime(1980, 6, 24, 4, 24, 2, tzinfo=datetime.timezone.utc)
jd = stime.get_julian_solar_day(date)
print(jd)
jde = stime.get_julian_ephemeris_day(date)
print(jde)
jc = stime.get_julian_century(jd)
print(jc)
jce = stime.get_julian_ephemeris_century(jde)
print(jce)
jme = stime.get_julian_ephemeris_millennium(jce)
print(jme)


L0 = sum([A * math.cos(B + C) for A,B,C in constants.heliocentric_longitude_coeffs[0]])
print(L0)
L1 = sum([A * math.cos(B + C) for A,B,C in constants.heliocentric_longitude_coeffs[1]])
print(L1)
L2 = sum([A * math.cos(B + C) for A,B,C in constants.heliocentric_longitude_coeffs[2]])
print(L2)
