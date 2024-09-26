#include "Enums.h"

std::string toUpper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return s;
}

CalendarKey stringToCalendarKey(const std::string& s) {
    std::string upper = toUpper(s);
    if (upper == "LON") return CalendarKey::LON;
    if (upper == "EUR") return CalendarKey::EUR;
    if (upper == "USD") return CalendarKey::USD;
    return CalendarKey::NONE;
}

RollConv stringToRollConv(const std::string& s) {
    std::string upper = toUpper(s);
    if (upper == "START") return RollConv::START;
    if (upper == "END") return RollConv::END;
    if (upper == "IMM") return RollConv::IMM;
    if (upper == "BEOM") return RollConv::BEOM;
    if (upper == "CEOM") return RollConv::CEOM;
    return RollConv::NONE;
}

BusinessDayConv stringToBusinessDayConv(const std::string& s) {
    std::string upper = toUpper(s);
    if (upper == "PRECEDING") return BusinessDayConv::PRECEDING;
    if (upper == "FOLLOWING") return BusinessDayConv::FOLLOWING;
    if (upper == "MOD_FOLLOWING") return BusinessDayConv::MOD_FOLLOWING;
    if (upper == "MOD_PRECEDING") return BusinessDayConv::MOD_PRECEDING;
    if (upper == "NO_ADJUSTMENT") return BusinessDayConv::NO_ADJUSTMENT;
    return BusinessDayConv::NONE;
}

DayCountConv stringToDayCountConv(const std::string& s) {
    std::string upper = toUpper(s);
    if (upper == "ACT365" || upper == "A365") return DayCountConv::ACT365;
    if (upper == "ACT360" || upper == "A360") return DayCountConv::ACT360;
    return DayCountConv::NONE;
}

CurveType stringToCurveType(const std::string& s) {
    std::string upper = toUpper(s);
    if (upper == "DISCOUNT") return CurveType::DISCOUNT;
    if (upper == "DISCOUNT_SPREAD") return CurveType::DISCOUNT_SPREAD;
    if (upper == "FORWARD_SPREAD") return CurveType::FORWARD_SPREAD;
    return CurveType::NONE;
}

CurveSplineType stringToCurveSplineType(const std::string& s) {
    std::string upper = toUpper(s);
    if (upper == "DISCOUNT") return CurveSplineType::DISCOUNT;
    if (upper == "BASE") return CurveSplineType::BASE;
    if (upper == "DISC_BASE") return CurveSplineType::DISC_BASE;
    if (upper == "TENOR") return CurveSplineType::TENOR;
    return CurveSplineType::NONE;
}

CurveCategory stringToCurveCategory(const std::string& s) {
    std::string upper = toUpper(s);
    if (upper == "IR") return CurveCategory::IR;
    if (upper == "FX") return CurveCategory::FX;
    if (upper == "EQUITY") return CurveCategory::EQUITY;
    if (upper == "CREDIT") return CurveCategory::CREDIT;
    return CurveCategory::NONE;
}

StubType stringToStubType(const std::string& s)
{
    std::string upper = toUpper(s);
    if (upper == "SS" || upper == "SHORTSTART") return StubType::ShortStart;
    if (upper == "LS" || upper == "LONGSTART") return StubType::LongStart;
    if (upper == "SE" || upper == "SHORTEND") return StubType::ShortEnd;
    if (upper == "LE" || upper == "LONGEND") return StubType::LongEnd;
    return StubType::NONE;
}
