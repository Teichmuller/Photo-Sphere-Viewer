#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <iostream>
#include <array>
#include <XMP.hpp>

using namespace std;

#define NOACTIONEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl;}}
#define GLOBALEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl; (final)(); exit(1);}}
#define LOCALEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl; (final)(); return false;}}
#define NULLPTREXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl; (final)(); return nullptr;}}

void NULLFUNCTION() {}

std::ostream &operator<<(std::ostream &os, XMP_DateTime const &d) {
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

enum XMPPropertyType
{
    Bool,
    Int,
    Int64,
    Float,
    Date,
    String
};

struct XMPProperty
{
    string Name;
    XMPPropertyType Type;
    bool IsRequired;
};


#endif // __UTILITIES_H__
