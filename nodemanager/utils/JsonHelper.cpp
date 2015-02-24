#include "JsonHelper.h"

namespace hpc
{
    /// FromJson/ToJson specializations.
    namespace utils
    {
        #define FROMJSON(T, Check, Fetch) \
        template <> \
        T JsonHelper<T>::FromJson(const json::value& j) \
        { \
            if (!j.is_null() && j.Check) { return j.Fetch; } \
            throw std::runtime_error("cannot get value from json object"); \
        }

        FROMJSON(int, is_number(), as_integer())
        FROMJSON(long, is_number(), as_number().to_int64())
        FROMJSON(std::string, is_string(), as_string())
        FROMJSON(const json::array&, is_array(), as_array())
        FROMJSON(long long, is_number(), as_number().to_int64())
        FROMJSON(double, is_number(), as_number().to_double())
        FROMJSON(bool, is_boolean(), as_bool())
        FROMJSON(const json::object&, is_object(), as_object())

        #define TOJSON(T, JsonType) \
        template <> \
        json::value JsonHelper<T>::ToJson(const T& val) { return json::value::JsonType(val); }

        TOJSON(int, number)
        TOJSON(double, number)
        TOJSON(bool, boolean)
        TOJSON(std::string, string)
    }
}
