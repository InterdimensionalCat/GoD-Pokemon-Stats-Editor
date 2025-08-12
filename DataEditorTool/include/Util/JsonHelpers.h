#pragma once

#ifndef IC_JSON_HELPERS
#define IC_JSON_HELPERS
namespace nlohmann
{
    template<>
    struct adl_serializer<ImColor, void> {

        static void to_json(json& j, const ImColor& Color);

        static void from_json(const json& j, ImColor& Color);
    };
}
#endif //IC_JSON_HELPERS
