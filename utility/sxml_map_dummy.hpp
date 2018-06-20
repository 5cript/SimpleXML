#pragma once

#include "../utility/sxml_attribute.hpp"
#include "../xml_parse/sxml_parse_fundamental.hpp"
#include "../xmlify/sxml_fundamental.hpp"
#include "../xmlify/sxml_optional.hpp"


#include <boost/fusion/adapted.hpp>

#include <type_traits>

namespace SXML
{
    namespace Internal
    {
        template <typename KeyT, typename ValueT, bool Mode = false /* parse */>
        struct map_dummy
        {
            SXML::Attribute <KeyT> id;
            using value_type_qualified = ValueT;
            ValueT value;

            map_dummy(KeyT const& id, value_type_qualified value)
                : id{id}
                , value{value}
            {
            }

            template <bool X = Mode,
                      typename = typename std::enable_if <!X, void>::type>
            map_dummy()
                : id{}
                , value{}
            {
            }

            template <bool X = Mode,
                      typename = typename std::enable_if <!X, void>::type>
            void xml_parse(NodeName const& name, PropertyTree const& tree, XmlParseOptions const& options = {})
            {
                SXML::xml_parse(id.get(), name >> "<xmlattr>.id", tree, options);
                SXML::xml_parse(value, name, tree, options);
            }

            template <bool X = Mode,
                      typename = typename std::enable_if <X, void>::type>
            std::ostream& xmlify(std::ostream& stream, std::string const& name, XmlifyOptions options) const
            {
                options.inObject = true;
                options.inArray = false;
                options.inLineCounter = 2;

                stream << "<" << name << " id=\"" << id << "\">";
                SXML::xmlify(stream, "nope", value, options);
                stream << "</" << name << ">";
                return stream;
            }
        };
    }
}
