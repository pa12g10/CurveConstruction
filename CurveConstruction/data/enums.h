#ifndef ENUMS_H
#define ENUMS_H

enum class CalendarKey { LON, EUR, USD };
enum class RollConv {START, END, IMM, BEOM, CEOM};
enum class BusinessDayConv { PRECEDING, FOLLOWING, MOD_FOLLOWING, MOD_PRECEDING, NO_ADJUSTMENT};
enum class DayCount { ACT365,  ACT360};

#endif // ENUMS_H