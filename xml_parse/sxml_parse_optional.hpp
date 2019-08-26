#pragma once

#include "sxml_parse_core.hpp"

#include <boost/optional.hpp>

#ifdef __has_include                           // Check if __has_include is present
#if __has_include(<optional>)                // Check for a standard library
#include <optional>
#endif
#endif // defined(__has_include)

namespace SXML
{
    template <typename T>
    void xml_parse(boost::optional <T>& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
    {
        try
        {
            if (!options.stateMixing)
                value = boost::none;

            if (object.tree.get_optional <std::string>(static_cast <std::string>(name)))
            {
                T v;
                xml_parse(v, name, object, options);
                value = v;
            }
        }
        SXML_DEFAULT_CATCH(boost::none, boost::none);
    }

#ifdef __has_include                           // Check if __has_include is present
#if __has_include(<optional>)
    template <typename T>
    void xml_parse(std::optional <T>& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
    {
        try
        {
            if (!options.stateMixing)
                value = std::nullopt;

            if (object.tree.get_optional <std::string>(static_cast <std::string>(name)))
            {
                T v;
                xml_parse(v, name, object, options);
                value = v;
            }
        }
        SXML_DEFAULT_CATCH(std::nullopt, std::nullopt);
    }
#endif
#endif // __has_include
}
