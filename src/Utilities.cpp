#include "utilities.h"

ostream &operator<<(ostream &os, XMP_DateTime const &d) {
    SXMPMeta meta;
//    if (d.hasDate)
//        os << d.year << '-' << d.month << '-' << d.day;
//    if (d.hasTime)
//        os << ' ' << d.hour << ':' << d.minute << ':' << d.second << "." << d.nanoSecond;
//    if (d.hasTimeZone)
//    {
//        switch (d.tzSign)
//        {
//        case kXMP_TimeIsUTC:
//            os << ' ' << "UTC";
//            break;
//        case kXMP_TimeWestOfUTC:
//            os << ' ' << "West" << " (-" << d.tzHour << ':' << d.tzMinute << ')';
//            break;
//        case kXMP_TimeEastOfUTC:
//            os << ' ' << "West" << " (+" << d.tzHour << ':' << d.tzMinute << ')';
//            break;
//        default:;
//        }
//    }
    string str;
    TXMPUtils<string>::ConvertFromDate(d, &str);
    os << str;
    return os;
}
