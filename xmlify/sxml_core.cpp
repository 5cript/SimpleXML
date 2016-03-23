#include "sxml_core.hpp"

namespace SXML { namespace Internal
{
//#####################################################################################################################
    std::ostream& tag_start(std::ostream& stream, std::string const& name, XmlifyOptions const& options)
    {
        stream << '<' << name << '>';

        return stream;
    }
//---------------------------------------------------------------------------------------------------------------------
    std::ostream& tag_end(std::ostream& stream, std::string const& name, XmlifyOptions const& options)
    {
        stream << "</" << name << '>';
        return stream;
    }
//#####################################################################################################################
}
}
