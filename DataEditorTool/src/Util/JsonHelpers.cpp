#include "include.h"
#include "Util/JsonHelpers.h"

void nlohmann::adl_serializer<ImColor, void>::to_json(ordered_json& j, const ImColor& Color)
{
    json ColorObj;
    ColorObj["R"] = Color.Value.x;
    ColorObj["G"] = Color.Value.y;
    ColorObj["B"] = Color.Value.z;
    ColorObj["A"] = Color.Value.w;

    j = ColorObj;
}

void nlohmann::adl_serializer<ImColor, void>::from_json(const ordered_json& j, ImColor& Color) {
    Color.Value.x = j["R"];
    Color.Value.y = j["G"];
    Color.Value.z = j["B"];
    Color.Value.w = j["A"];
}
