#pragma once

#include "sxml_core.hpp"
#include <string>

namespace SXML
{
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::string const& value, XmlifyOptions const& options = {});
}
