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
	 * \struct adl_serializer<ImColor, void>
     * \brief  Serialize an ImColor to/from JSON.
     */
    struct adl_serializer<ImColor, void> {
        
		/**
		 * Serialize an ImColor to JSON.
		 * 
		 * \param j The JSON object to serialize to.
		 * \param Color The ImColor to serialize.
		 */
        static void to_json(ordered_json& j, const ImColor& Color);

		/**
		 * Deserialize an ImColor from JSON.
		 * 
		 * \param j The JSON object to deserialize from.
		 * \param Color The ImColor to deserialize to.
		 */
        static void from_json(const ordered_json& j, ImColor& Color);
    };
}
#endif //IC_JSON_HELPERS
