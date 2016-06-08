#pragma once

#include "sxml_core.hpp"
#include "../utility/sxml_object.hpp"
#include "../utility/sxml_content.hpp"

#include <boost/fusion/mpl.hpp>
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
        memberTypeDependendXmlifier(std::ostream& stream, bool attributeRun, bool& anyMembers, std::string const& name, U const& value, XmlifyOptions const& options)
        {
            if (!attributeRun)
                return;
            stream << ' ' << name << '=' << options.attributeQuotes << value.value << options.attributeQuotes;
        }

        template <typename U>
        typename std::enable_if <!isAttribute<U>::value && !isContent<U>::value>::type
        memberTypeDependendXmlifier(std::ostream& stream, bool attributeRun, bool& anyMembers, std::string const& name, U const& value, XmlifyOptions const& options)
        {
            if (attributeRun)
                return;
            if (!anyMembers)
                stream << '>';
            anyMembers = true;
            xmlify(stream, name, value, options);
        }

        template <typename U>
        typename std::enable_if <isContent<U>::value>::type
        memberTypeDependendXmlifier(std::ostream& stream, bool attributeRun, bool& anyMembers, std::string const& name, U const& value, XmlifyOptions const& options)
        {
            if (attributeRun)
                return;
            if (!anyMembers)
                stream << '>';
            anyMembers = true;
            stream << static_cast <typename U::type>(value);
        }
    }

    template <typename T>
    class AdaptedXmlifier
    {
    public:
        std::ostream& operator()(std::ostream& stream, std::string const& name, T const& object, XmlifyOptions const& options) const
        {
            typedef boost::mpl::range_c <
                int,
                0,
                boost::fusion::result_of::size<T>::type::value
            > range;

            stream << '<' << name;

            bool anyMembers = false;

            // attribute run
            boost::mpl::for_each <range> (std::bind <void>(
                _helper(boost::fusion::result_of::size<T>::type::value),
                std::placeholders::_1,
                true,
                std::ref(anyMembers),
                std::ref(stream),
                std::cref(object),
                std::cref(options))
            );

            // member run
            boost::mpl::for_each <range> (std::bind <void>(
                _helper(boost::fusion::result_of::size<T>::type::value),
                std::placeholders::_1,
                false,
                std::ref(anyMembers),
                std::ref(stream),
                std::cref(object),
                std::cref(options))
            );

            if (!anyMembers)
            {
                if (options.noSpace)
                    stream << "/>";
                else
                    stream << " />";
            }
            else
                Internal::tag_end(stream, name, options);
            return stream;
        }
    private:
        class _helper
        {
        public:
            template <typename Index>
            void operator()(Index, bool attributeRun, bool& anyMembers, std::ostream& os, T const& object, XmlifyOptions const& options) const
            {
                auto const& member = boost::fusion::at <Index> (object);

                Internal::memberTypeDependendXmlifier <typename std::decay <decltype(member)>::type> (
                    os,
                    attributeRun,
                    anyMembers,
                    boost::fusion::extension::struct_member_name <T, Index::value>::call(),
                    member,
                    options
                );
            }
            _helper(int len) : len(len) {}
        private:
            int len;
        };
    };

    template <typename Derived>
    struct Xmlifiable
    {
        std::ostream& xmlify(std::ostream& stream, std::string const& name, XmlifyOptions options) const
        {
            options.inObject = true;
            AdaptedXmlifier <Derived> xmlifier;
            options.inArray = false;
            return xmlifier(stream, name, *static_cast <Derived const*> (this), options);
        }
        virtual ~Xmlifiable() = default;
    };

    template <typename T,
              class = typename std::enable_if <std::is_class <T>::value>::type,
              class = typename std::enable_if <Internal::isXmlObject <T>::value>::type>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, T const& value, XmlifyOptions const& options = {})
    {
        using namespace Internal;

        value.xmlify(stream, name, options);
        return stream;
    }
}
