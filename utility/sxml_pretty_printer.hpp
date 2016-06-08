#pragma once

#include <iosfwd>

namespace SXML
{
    namespace Internal
    {
        struct PrettyCopyContext
        {
            bool escaped = false;
            bool disabled = false;

            int indentationLevel = 0;
            char previous = '\0';

            bool inTag = false;
            bool isClosingTag = false;
            bool previousWasClosingTag = false;
        };
    }

    void prettyCopy(std::ostream& output, std::istream& input);
}
