#pragma once


namespace PikaUtils
{

/*
 * Class for computing the various times required for solar incident angle calculations.
 */
class DateTime
{
public:
  enum class Format{ISO8601};
  DateTime(const std::string & date, Format format = Format::ISO8601);
  DateTime(int year, int month, int day, int hours, int minutes, double seconds);
  void add(int years, int months, int day, int hours, int minutes, double seconds);

  int year() const {return _tinfo.tm_year + 1900;}
  int month() const {return _tinfo.tm_mon + 1;}
  int day() const {return _tinfo.tm_mday;}
  int hour() const {return _tinfo.tm_hour;}
  int minute() const {return _tinfo.tm_min;}
  double second() const {return _fraction_sec + static_cast<double>(_tinfo.tm_sec);}

private:
  struct tm _tinfo;
  double _fraction_sec = 0;
};

} // namespace
