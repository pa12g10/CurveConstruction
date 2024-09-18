#include "OISSwap.h"
#include "../src/utils/Date.h"

OISSwap::OISSwap(const Date& _value_date, VectorOfDictionaries& _ois_instruments) : value_date(_value_date), instruments(_ois_instruments)
{
    for (auto& instrument : instruments) {
        setInstrumentMaturity(instrument);
    }
}


void OISSwap::setInstrumentMaturity(Dictionary& instrument) {
    auto spot_days = getValueFromVariant<std::string>(instrument["StartDate"]);
    auto calendar_key = getValueFromVariant<std::string>(instrument["FixingCalendar"]);
    auto tenor = getValueFromVariant<std::string>(instrument["Maturity"]);
    
    Date effective_date = value_date.addDurationBusinessDay(spot_days, stringToCalendarKey(calendar_key), BusinessDayConv::FOLLOWING);
    Date unadjusted_maturity_date = effective_date.addDuration(tenor);

    instrument["UnadjustedMaturityDate"] = Date::dateToString(unadjusted_maturity_date);
    instrument["EffectiveDate"] = Date::dateToString(effective_date);

}

std::vector<double> OISSwap::objectiveFunction()
{
    return std::vector<double>();
}

Dictionary OISSwap::price(const Dictionary& instrument, const DictionaryOfFunctors& rates_map)
{
    return Dictionary();
}