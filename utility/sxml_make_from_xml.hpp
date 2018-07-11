#pragma once

#include "../xml_parse/sxml_generic_parser.hpp"

namespace SXML
{
    template <typename T, typename U>
    T make_from_xml(U&& input, XmlParseOptions options = {})
    {
        auto tree = parse_xml(std::forward <U&&>(input));
        if (tree.tree.empty())
            return T{};
        auto root = tree.tree.front();
        T result;
        xml_parse(result, root.first, tree, options);
        return result;
    }
}
