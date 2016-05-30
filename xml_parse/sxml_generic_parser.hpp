#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/optional.hpp>

namespace SXML
{
    struct PropertyTree
    {
        boost::property_tree::ptree tree;

        PropertyTree(boost::property_tree::ptree tree = {});
    };

    PropertyTree parse_xml(std::istream& stream);
    PropertyTree parse_xml(std::string const& str);
}
