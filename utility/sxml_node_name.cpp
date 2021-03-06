#include "sxml_node_name.hpp"

#include <boost/algorithm/string.hpp>

namespace SXML
{
//#####################################################################################################################
    NodeName::NodeName(std::string const& name)
        : chain_(NodeName::split(name))
    {
    }
//---------------------------------------------------------------------------------------------------------------------
    NodeName::NodeName(char const* name)
        : NodeName(std::string(name))
    {
    }
//---------------------------------------------------------------------------------------------------------------------
    NodeName& NodeName::operator=(std::string const& name)
    {
        chain_ = NodeName::split(name);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    NodeName NodeName::operator>>(NodeName const& other) const
    {
        NodeName n;
        n.chain_.reserve(chain_.size() + other.chain_.size());
        n.chain_.insert(n.chain_.end(), chain_.begin(), chain_.end());
        n.chain_.insert(n.chain_.end(), other.chain_.begin(), other.chain_.end());
        return n;
    }
//---------------------------------------------------------------------------------------------------------------------
    NodeName::operator std::string() const
    {
        return toString();
    }
//---------------------------------------------------------------------------------------------------------------------
    bool NodeName::empty() const
    {
        return chain_.empty();
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string NodeName::getName() const
    {
        if (chain_.empty())
            return {};

        return chain_.back();
    }
//---------------------------------------------------------------------------------------------------------------------
    NodeName NodeName::parent() const
    {
        NodeName n;
        n.chain_ = chain_;
        n.chain_.pop_back();
        return n;
    }
//---------------------------------------------------------------------------------------------------------------------
    NodeName NodeName::child(std::string const& name) const
    {
        NodeName n;
        n.chain_ = chain_;
        n.chain_.push_back(name);
        return n;
    }
//---------------------------------------------------------------------------------------------------------------------
    NodeName& NodeName::operator+=(std::string const& name)
    {
        chain_.push_back(name);
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string NodeName::toString() const
    {
        if (chain_.empty())
            return {};

        std::string result;
        for (auto i = std::begin(chain_), end = std::end(chain_) - 1; i < end; ++i)
        {
            result += *i;
            result.push_back('.');
        }
        result += *(std::end(chain_) - 1);
        return result;
    }
//---------------------------------------------------------------------------------------------------------------------
    std::vector <std::string> NodeName::split(std::string const& name)
    {
        if (name.empty())
            return {};

        std::vector <std::string> splitUp;
        boost::split(splitUp, name, boost::is_any_of("."));
        return splitUp;
    }
//#####################################################################################################################
}
