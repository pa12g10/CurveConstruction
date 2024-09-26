#ifndef ENUMS_H
#define ENUMS_H
#include <string>
#include <unordered_map>
#include <algorithm>

enum class CalendarKey { LON, EUR, USD, NONE };
enum class RollConv { START, END, IMM, BEOM, CEOM, NONE };
enum class BusinessDayConv { PRECEDING, FOLLOWING, MOD_FOLLOWING, MOD_PRECEDING, NO_ADJUSTMENT, NONE };
enum class DayCountConv { ACT365, ACT360, NONE };
enum class CurveType { DISCOUNT, DISCOUNT_SPREAD, FORWARD_SPREAD, NONE };
enum class CurveSplineType { DISCOUNT, BASE, DISC_BASE, TENOR, NONE };
enum class CurveCategory { IR, FX, EQUITY, CREDIT, NONE };
enum class StubType { ShortStart, LongStart , ShortEnd, LongEnd,  NONE };

// Helper function to convert string to uppercase
std::string toUpper(std::string s); 

// Functions to convert strings to enum values
CalendarKey stringToCalendarKey(const std::string& s);

RollConv stringToRollConv(const std::string& s);

BusinessDayConv stringToBusinessDayConv(const std::string& s);

DayCountConv stringToDayCountConv(const std::string& s);

CurveType stringToCurveType(const std::string& s);

CurveSplineType stringToCurveSplineType(const std::string& s);

CurveCategory stringToCurveCategory(const std::string& s);

StubType stringToStubType(const std::string& s);


#endif // ENUMS_H
