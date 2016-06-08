#include "sxml_pretty_printer.hpp"

#include <vector>
#include <iostream>

namespace SXML
{
//#####################################################################################################################
    void prettyCopy(std::ostream& output, std::istream& input)
    {
        constexpr char indent = '\t';

        Internal::PrettyCopyContext context;
        std::vector <char> buffer;

        // returns true if within "".
        auto escaping = [&context](char c)
        {
            context.escaped = false;
            if (context.disabled)
                if (c == '\\')
                    context.escaped = true;

            if (c == '"' && !context.escaped)
                context.disabled = !context.disabled;

            if (context.disabled)
                return true;
            return false;
        };

        auto put = [&](char c)
        {
            buffer.push_back(c);
        };

        auto flush = [&](bool includeProtoSpace)
        {
            for (auto const& c : buffer)
            {
                if (includeProtoSpace && c == '\0')
                    output.put(indent);
                else if (c != '\0')
                    output.put(c);
            }
            buffer.clear();
        };

        int c, eof = std::istream::traits_type::eof();
        while ((c = input.get()) != eof)
        {
            if (escaping(c))
            {
                put(c);
                continue;
            }

            if (c == '<')
            {
                if (context.previous == '>')
                    put('\n');

                if (context.previous == '>')
                {
                    for (int i = 0; i < context.indentationLevel - 1; ++i)
                        put(indent);
                    put('\0');
                }

                put(c);

                context.inTag = true;
                context.isClosingTag = false;
            }
            else if (c == '>')
            {
                put(c);

                context.inTag = false;

                if (context.previous != '/')
                {
                    if (!context.isClosingTag)
                        context.indentationLevel++;
                    else
                        context.indentationLevel--;
                }

                if (context.isClosingTag && context.previous != '/')
                    flush(false);
                else
                    flush(true);

                context.previousWasClosingTag = context.isClosingTag;
            }
            else if (c == '/' && context.inTag)
            {
                context.isClosingTag = true;
                put(c);
            }
            else
                put(c);

            context.previous = c;
        }
    }
//---------------------------------------------------------------------------------------------------------------------
//#####################################################################################################################
}
