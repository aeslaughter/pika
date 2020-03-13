#include <regex>
#include <ctime>
#include <sstream>


#include "DateTime.h"


namespace PikaUtils
{


DateTime::DateTime(const std::string & date, Format format)
{
  std::regex re;
  switch (format)
  {
  case Format::ISO8601:
    re ="([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})(?:\\.([0-9]+))?(?:([+-])([0-2][0-9]):([0-6][0-9]))?";
  }
  std::smatch match;
  std::regex_match(date, match, re);

  _tinfo.tm_year = std::stoi(match[1]) - 1900;
  _tinfo.tm_mon = std::stoi(match[2]) - 1;
  _tinfo.tm_mday = std::stoi(match[3]);
  _tinfo.tm_hour = std::stoi(match[4]);
  _tinfo.tm_min = std::stoi(match[5]);
  _tinfo.tm_sec = std::stoi(match[6]);
  _tinfo.tm_isdst = 0;

  if (match[7].matched)
  {
    std::ostringstream oss;
    oss << "0." << match[7];
    _fraction_sec = std::stod(oss.str());
  }

  int sign = match[8] == "-" ? -1 : 1;
  int tz_hour = match[9].matched ? sign * std::stoi(match[9]) : 0;
  int tz_min = match[10].matched ? sign * std::stoi(match[10]) : 0;
  _tinfo.tm_hour -= tz_hour;
  _tinfo.tm_min -= tz_min;
  mktime(&_tinfo);
}

DateTime::DateTime(int year, int month, int day, int hours, int minutes, double seconds)
{
  _tinfo.tm_year = year - 1900;
  _tinfo.tm_mon = month - 1;
  _tinfo.tm_mday = day;
  _tinfo.tm_hour = hours;
  _tinfo.tm_min = minutes;
  _fraction_sec = modf(seconds , &seconds);
  _tinfo.tm_sec = seconds;
  mktime(&_tinfo);
}


void
DateTime::add(int years, int months, int days, int hours, int minutes, double seconds)
{
  _tinfo.tm_year += years;
  _tinfo.tm_mon += months;
  _tinfo.tm_mday += days;
  _tinfo.tm_hour += hours;
  _tinfo.tm_min += minutes;

  seconds += _tinfo.tm_sec;
  _fraction_sec = modf(seconds , &seconds);
  _tinfo.tm_sec = static_cast<int>(seconds);
  mktime(&_tinfo);
}

} // namespace
