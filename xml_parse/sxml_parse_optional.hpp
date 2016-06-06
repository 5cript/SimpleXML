#pragma once

#include "sxml_parse_core.hpp"

#include <boost/optional.hpp>

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
        DEFAULT_CATCH(boost::none, boost::none);
    }
}
