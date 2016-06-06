#pragma once

#include "sxml_mixin.hpp"
#include "../xmlify/sxml_core.hpp"
#include "../xml_parse/sxml_parse_core.hpp"

namespace SXML
{
    template <typename Parent, typename Name>
    struct Wrapper;

    template <typename ContainerT, typename Name>
    using Wrap = MixinHelper <ContainerT, Wrapper <ContainerT, Name>>;

    template <typename WrappedT, typename Name>
    class Wrapper
    {
    public:
        Wrapper(WrappedT* wrapped)
            : wrapped_(wrapped)
        {
        }

        std::ostream& xmlify(std::ostream& stream, std::string const& name, XmlifyOptions options) const
        {
            /*
            tag_start(stream, Name::c_str, options);
            xmlify(stream, name, *wrapped_, options);
            tag_end(stream, Name::c_str, options);
            */
            return stream;
        }
        void xml_parse(NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
        {
            //xml_parse(name.child())
        }

    private:
        WrappedT* wrapped_;
    };
}
