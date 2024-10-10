#include "OISSwap.h"


OISSwapPricer::OISSwapPricer(const int& _value_date, VectorOfDictionaries& _ois_instruments) : value_date(_value_date),
instruments(_ois_instruments)
{
    for (auto& instrument : instruments) {
        setInstrumentMaturity(instrument);
    }
}


void OISSwapPricer::setInstrumentMaturity(Dictionary& instrument) {
    auto spot_days = getValueFromVariant<std::string>(instrument["StartDate"]);
    auto calendar_key = getValueFromVariant<std::string>(instrument["FixingCalendar"]);
    auto tenor = getValueFromVariant<std::string>(instrument["Maturity"]);
    
    int effective_date = DateUtilities::addDurationBusinessDay(value_date, spot_days, stringToCalendarKey(calendar_key), 
        BusinessDayConv::FOLLOWING);
    int unadjusted_maturity_date = DateUtilities::addDuration(effective_date, tenor);

    instrument["UnadjustedMaturityDate"] = unadjusted_maturity_date;
    instrument["MaturityDate"] = DateUtilities::businessDayAdjusted(unadjusted_maturity_date, stringToCalendarKey(calendar_key),
        BusinessDayConv::FOLLOWING);
    instrument["EffectiveDate"] = effective_date;
}

Dictionary OISSwapPricer::getCurveKeys(Dictionary& instrument) {
    Dictionary curve_codes = Dictionary();
    auto exchange = getValueFromVariant<std::string>(instrument["Exchange"]);
    auto currency = getValueFromVariant<std::string>(instrument["Currency"]);
    auto refrence_rate = getValueFromVariant<std::string>(instrument["ReferenceRate"]);

    auto accrual_curve_key = "IR_" + currency  + "_" + exchange + "_" + refrence_rate + "_DF";
    curve_codes["AccrualCurveKey"] = accrual_curve_key;
    curve_codes["DiscountCurveKey"] = accrual_curve_key;
    return curve_codes;
}

Dictionary OISSwapPricer::price(Dictionary& instrument, DictionaryOfFunctors& rates_map)
{
    auto start_date = getValueFromVariant<int>(instrument["EffectiveDate"]);
    auto pay_delay = getValueFromVariant<std::string>(instrument["PayDelay"]);
    auto unadj_maturity_date = getValueFromVariant<int>(instrument["UnadjustedMaturityDate"]);
    auto fixed_leg_frequency = getValueFromVariant<std::string>(instrument["FixedLegFrequency"]);
    auto float_leg_frequency = getValueFromVariant<std::string>(instrument["FloatLegFrequency"]);
    auto calendar_key = getValueFromVariant<std::string>(instrument["AccrualCalendar"]);
    auto stub_type = getValueFromVariant<std::string>(instrument["StubType"]);
    auto dcc = stringToDayCountConv(getValueFromVariant<std::string>(instrument["FixedLegDCC"]));
    auto bdc = getValueFromVariant<std::string>(instrument["DayCountConvetion"]);
    auto roll_conv = getValueFromVariant<std::string>(instrument["RollConvention"]);
    auto fixed_rate = getValueFromVariant<double>(instrument["Rate"]);


    Dictionary curve_codes = getCurveKeys(instrument);
    std::string discount_curve_key = getValueFromVariant<std::string>(curve_codes["DiscountCurveKey"]);
    std::string accural_curve_key = getValueFromVariant<std::string>(curve_codes["AccrualCurveKey"]);

    auto disc_curve = rates_map[discount_curve_key];
    auto accrual_curve = rates_map[accural_curve_key];

    vector<CashflowDates> fixed_leg_cfs = CashflowScheduler::generateCashflows(start_date, unadj_maturity_date, pay_delay, 
        stringToCalendarKey(calendar_key), stringToStubType(stub_type), fixed_leg_frequency, stringToBusinessDayConv(bdc) , stringToRollConv(roll_conv));

    vector<CashflowDates> float_leg_cfs = CashflowScheduler::generateCashflows(start_date, unadj_maturity_date, pay_delay,
        stringToCalendarKey(calendar_key), stringToStubType(stub_type), float_leg_frequency, stringToBusinessDayConv(bdc), stringToRollConv(roll_conv));
    
    
    Dictionary results = Dictionary();
    double par_rate = 0.0, pv = 0.0;
    double fixed_leg = 0.0, float_leg = 0.0, annuity = 0.0;
    
    for (auto& cf : fixed_leg_cfs)
    {
        int reset_start_date = cf.adjusted_start_date;
        int reset_end_date = cf.adjusted_end_date;
        int payment_date = cf.payment_date;
        
        double reset_start_date_df = accrual_curve((int)reset_start_date);
        double reset_end_date_df = accrual_curve((int)reset_end_date);
        double accrual_year_fract = DateUtilities::yearFraction(reset_start_date, reset_end_date, dcc);
        double fwd = 1 / accrual_year_fract * (reset_start_date_df / reset_end_date_df - 1);

        double  payment_date_df = disc_curve((int)payment_date);

        float_leg += accrual_year_fract * payment_date_df * fwd;
        fixed_leg += accrual_year_fract * payment_date_df * fixed_rate;
        annuity += accrual_year_fract * payment_date_df;

    }

    pv = fixed_leg - float_leg;
    par_rate = float_leg / annuity;
    results["CalculatedRate"] = par_rate;
    results["PV"] = pv;

    return results;
}

std::vector<double> OISSwapPricer::objectiveFunction(DictionaryOfFunctors& _rates_map)
{
    auto residulals = std::vector<double>();
    for (auto& instrument : instruments) {
        auto instrument_results = this->price(instrument, _rates_map);
        double par_rate = getValueFromVariant<double>(instrument["Rate"]);
        double calc_par_rate = getValueFromVariant<double>(instrument_results["CalculatedRate"]);
        double residual = par_rate - calc_par_rate;
        residulals.push_back(residual);
    }
    return residulals;
}