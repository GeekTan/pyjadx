#pragma once

#include <jni/object.hpp>
#include <jni/array.hpp>
#include <jni/make.hpp>
#include <jni/npe.hpp>

#include <locale>
#include <codecvt>

namespace jni
   {
    using String = Object<StringTag>;

    inline std::u16string MakeAnything(ThingToMake<std::u16string>, JNIEnv& env, const String& string)
       {
        NullCheck(env, string.get());
        std::u16string result(jni::GetStringLength(env, *string), char16_t());
        jni::GetStringRegion(env, *string, 0, result);
        return result;
       }

    inline std::string MakeAnything(ThingToMake<std::string>, JNIEnv& env, const String& string)
       {
        return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>()
            .to_bytes(Make<std::u16string>(env, string));
       }

    inline Local<String> MakeAnything(ThingToMake<String>, JNIEnv& env, const std::u16string& string)
       {
        return Local<String>(env, &NewString(env, string));
       }

    inline Local<String> MakeAnything(ThingToMake<String>, JNIEnv& env, const std::string& string)
       {
        return Make<String>(env, std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>()
            .from_bytes(string));
       }
   }
