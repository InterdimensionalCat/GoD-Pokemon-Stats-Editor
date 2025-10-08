/*****************************************************************//**
 * \file   JsonHelpers.h
 * \brief  Static helper functions for serializing and deserializing
 * custom types to and from JSON using nlohmann::json.
 * 
 * \author Bennett Thomas
 * \date   September 2025
 *********************************************************************/
#pragma once

#ifndef IC_JSON_HELPERS
#define IC_JSON_HELPERS
namespace nlohmann
{

    template<>
    /**
	 * \struct adl_serializer
     * \brief  Serialize an ImColor to/from JSON.
     */
    struct adl_serializer<ImColor, void> {
        
		/** Serialize an ImColor to JSON. */
        static void to_json(ordered_json& j, const ImColor& Color);

		/** Deserialize an ImColor from JSON. */
        static void from_json(const ordered_json& j, ImColor& Color);
    };
}
#endif //IC_JSON_HELPERS
