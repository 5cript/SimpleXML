#include "sxml_parse_string.hpp"

namespace SXML
{
    void xml_parse(std::string& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
    {
        try
        {
            GET_VALUE(std::string, name, value, "");
        }
        DEFAULT_CATCH("", "")
    }
}
