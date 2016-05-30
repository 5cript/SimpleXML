#include "sxml_generic_parser.hpp"
#include <boost/property_tree/xml_parser.hpp>

namespace SXML
{
	using namespace boost::property_tree;
//#####################################################################################################################
    PropertyTree::PropertyTree(boost::property_tree::ptree tree)
        : tree{std::move(tree)}
    {

    }
//#####################################################################################################################
    PropertyTree parse_xml(std::istream& stream)
    {
        ptree pt;
        read_xml(stream, pt);
        return {pt};
    }
//---------------------------------------------------------------------------------------------------------------------
    PropertyTree parse_xml(std::string const& str)
    {
        std::stringstream sstr(str);

        ptree pt;
        read_xml(sstr, pt);
        return {pt};
    }
//#####################################################################################################################
}
