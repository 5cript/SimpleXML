#pragma once

#include <string>
#include <utility>
#include <type_traits>
#include <iosfwd>

#include "../utility/sxml_attribute.hpp"
#include "sxml_options.hpp"

namespace SXML
{
    namespace Internal
    {
        std::ostream& tag_start(std::ostream& stream, std::string const& name, XmlifyOptions const& options);
        std::ostream& tag_end(std::ostream& stream, std::string const& name, XmlifyOptions const& options);
    }
}
