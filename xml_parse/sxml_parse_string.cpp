#include "sxml_parse_string.hpp"

namespace SXML
{
    void xml_parse(std::string& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
    {
        try
        {
            SXML_GET_VALUE(std::string, name, value, "");
        }
        SXML_DEFAULT_CATCH("", "")
    }
}
