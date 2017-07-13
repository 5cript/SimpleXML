#pragma once

#include "sxml_parse_core.hpp"
#include "../utility/sxml_object.hpp"
#include "../utility/sxml_content.hpp"
#include "../utility/sxml_inline.hpp"

#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>


namespace SXML
{
    namespace Internal
    {
        template <typename U>
        typename std::enable_if <isAttribute<U>::value>::type
        memberTypeDependendParser(U& value, bool attributeRun, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
        {
            if (!attributeRun)
                return;

            xml_parse(value.get(), name, object, options);
        }

        template <typename U>
        typename std::enable_if <isContent<U>::value>::type
        memberTypeDependendParser(U& value, bool attributeRun, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
        {
            if (attributeRun)
                return;

            try
            {
                typename U::type& v = value.get();
                SXML_GET_VALUE(typename U::type, name.parent().toString(), v, typename U::type{});
            }
            SXML_DEFAULT_CATCH(typename U::type{}, typename U::type{})
        }

        template <typename U>
        typename std::enable_if <isInline<U>::value>::type
        memberTypeDependendParser(U& value, bool attributeRun, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
        {
            if (attributeRun)
                return;

            xml_parse(value.get(), name, object, options);
        }

        template <typename U>
        typename std::enable_if <!isAttribute<U>::value && !isContent<U>::value && !isInline<U>::value>::type
        memberTypeDependendParser(U& value, bool attributeRun, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
        {
            if (attributeRun)
                return;

            xml_parse(value, name, object, options);
        }
    }

    template <typename T>
    class AdaptedParser
    {
    public:
        void operator()(T& object, NodeName const& name, PropertyTree const& tree, XmlParseOptions const& options) const
        {
            //! If you get an Error here, you likely forgot to use BOOST_FUSION_ADAPT_STRUCT !

            typedef boost::mpl::range_c<
                int,
                0,
                boost::fusion::result_of::size <T>::type::value
            > range;

            // attribute run
            boost::mpl::for_each <range> (
                [&](auto Index) {
                    _helper h{boost::fusion::result_of::size <T>::type::value};
                    h(Index, true, object, name, tree, options);
                }
            );

            // member run
            boost::mpl::for_each <range> (
                [&](auto Index) {
                    _helper h{boost::fusion::result_of::size <T>::type::value};
                    h(Index, false, object, name, tree, options);
                }
            );
        }
    private:
        class _helper
        {
        public:
            template<class Index>
            void operator()(Index, bool attributeRun, T& object, NodeName const& name, PropertyTree const& tree, XmlParseOptions const& options) const
            {
                auto& member = boost::fusion::at <Index> (object);

                std::string tempName;

                if (!name.empty())
                    tempName = static_cast <std::string> (name) + ".";
                if (attributeRun)
                    tempName += "<xmlattr>.";

                tempName += boost::fusion::extension::struct_member_name<T, Index::value>::call();

                Internal::memberTypeDependendParser <typename std::decay <decltype(member)>::type> (
                    member,
                    attributeRun,
                    tempName,
                    tree,
                    options
                );
            }
            _helper(int len) : len(len) {}
        private:
            int len;
        };
    };

    template <typename Derived>
    struct Parsable
    {
        void xml_parse(NodeName const& name, PropertyTree const& tree, XmlParseOptions const& options = {})
        {
            AdaptedParser <Derived> parser;
            parser(*static_cast <Derived*> (this), name, tree, options);
        }
        virtual ~Parsable() = default;
    };
}
