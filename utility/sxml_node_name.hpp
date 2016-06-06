#pragma once

#include <vector>
#include <string>

namespace SXML
{
    class NodeName
    {
    public:
        NodeName() = default;

        NodeName(std::string const& name);
        NodeName(char const* name);

        NodeName& operator=(std::string const& name);

        NodeName(NodeName const&) = default;
        NodeName(NodeName&&) = default;

        NodeName& operator=(NodeName const&) = default;
        NodeName& operator=(NodeName&&) = default;

        explicit operator std::string() const;
        std::string toString() const;

        /// Returns the name of this exact node without the path.
        std::string getName() const;

        NodeName parent() const;
        NodeName child(std::string const& name) const;
        NodeName& operator+=(std::string const& name);

        bool empty() const;

    private:
        static std::vector <std::string> split(std::string const& name);

    private:
        std::vector <std::string> chain_; // sorted correctly all time.
    };
}
