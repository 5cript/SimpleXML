#include "sxml_options.hpp"

namespace SXML
{
//#####################################################################################################################
    XmlifyOptions XmlifyOptions::withoutTags() const
    {
        XmlifyOptions clone = *this;
        clone.noTags = true;
        return clone;
    }
//#####################################################################################################################
}
