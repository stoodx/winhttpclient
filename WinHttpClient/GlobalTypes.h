
#ifndef __GLOBAL_TYPES_H__
#define __GLOBAL_TYPES_H__

#include <vector>
#include <string>
#include <set>
#include <tchar.h>

//TODO: DECRYPT && CREATE MACRO FOR EACH STRING.
#define TXET(s) s

//#define json_key(x) x

#ifdef _UNICODE 
  namespace std {
    typedef wstring tstring;
  }

#else
  namespace std {
    typedef string tstring;
  }
#endif

#define MS_IN_HOUR 3600000
#define MS_IN_MINUTE 60000

#include <locale>
#include <codecvt>
inline std::wstring s2ws(const std::string& str)
{
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

inline std::string ws2s(const std::wstring& wstr)
{
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

enum class NULLABLE_BOOL {
  BOOL_ERROR = 0,
  BOOL_NO = 1,
  BOOL_YES = 2
};


#endif //__GLOBAL_TYPES_H__


