#pragma once

#include "sxml_core.hpp"

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
        struct isAttribute
        {
            constexpr static const bool value = false;
        };

        template <typename U>
        struct isAttribute <Attribute <U>>
        {
            constexpr static const bool value = true;
        };

        template <typename U>
        typename std::enable_if <isAttribute<U>::value>::type
        memberTypeDependendXmlifier(std::ostream& stream, bool attributeRun, std::string const& name, U const& value, XmlifyOptions const& options)
        {
            if (!attributeRun)
                return;
            stream << ' ' << name << '=' << options.attributeQuotes << value.value << options.attributeQuotes;
        }

        template <typename U>
        typename std::enable_if <!isAttribute<U>::value>::type
        memberTypeDependendXmlifier(std::ostream& stream, bool attributeRun, std::string const& name, U const& value, XmlifyOptions const& options)
        {
            if (attributeRun)
                return;
            xmlify(stream, name, value, options);
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

            // attribute run
            boost::mpl::for_each <range> (std::bind <void>(
                _helper(boost::fusion::result_of::size<T>::type::value),
                std::placeholders::_1,
                true,
                std::ref(stream),
                std::ref(object),
                std::ref(options))
            );

            stream << '>';

            // member run
            boost::mpl::for_each <range> (std::bind <void>(
                _helper(boost::fusion::result_of::size<T>::type::value),
                std::placeholders::_1,
                false,
                std::ref(stream),
                std::ref(object),
                std::ref(options))
            );

            Internal::tag_end(stream, name, options);
            return stream;
        }
    private:
        class _helper
        {
        public:
            template <typename Index>
            void operator()(Index, bool attributeRun, std::ostream& os, T const& object, XmlifyOptions const& options) const
            {
                auto const& member = boost::fusion::at <Index> (object);

                Internal::memberTypeDependendXmlifier<typename std::decay <decltype(member)>::type>(os, attributeRun, boost::fusion::extension::struct_member_name <T, Index::value>::call(), member, options);
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
            return xmlifier(stream, name, *static_cast <Derived const*> (this), options);
        }
        virtual ~Xmlifiable() = default;
    };

    namespace Internal
    {
        template <typename Type,
                   class = typename std::enable_if <std::is_class <Type>::value>::type>
        class isXmlObject
        {
            class yes { char m; };
            class no { yes m[2]; };

            struct BaseMixin
            {
                std::ostream& xmlify(std::ostream& stream, std::string const&, XmlifyOptions) const { return stream; }
            };
            struct Base : public Type, public BaseMixin {};

            template <typename T, T> class Helper {};

            template <typename U>
            static no deduce(U*, Helper <std::ostream& (BaseMixin::*)(std::ostream&, std::string const&, XmlifyOptions), &U::xmlify>* = nullptr);

            static yes deduce(...);

        public:
            static const bool value = sizeof(yes) == sizeof(deduce((Base*)(nullptr)));
        };
    }

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
