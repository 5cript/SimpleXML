#pragma once

namespace SXML
{
    namespace Internal
    {
        template <typename Type, typename enable = void>
        class isParsable
        {
        public:
            static const bool value = false;
        };

        template <typename Type>
        class isParsable <Type, typename std::enable_if<std::is_class<Type>::value>::type>
        {
        private:
            class yes { char m; };
            class no { yes m[2];};
            struct BaseMixin
            {
                void xml_parse(std::string const&,
                               PropertyTree const&,
                               XmlParseOptions const&)
                {}
            };
            struct Base : public Type, public BaseMixin {};
            template <typename T, T t>  class Helper{};

            template <typename U>
            static no deduce(U*, Helper<
                void (BaseMixin::*)(std::string const&,
                                    PropertyTree const&,
                                    XmlParseOptions const&),
                &U::parse>* = nullptr);
            static yes deduce(...);
        public:
            static const bool value = sizeof(yes) == sizeof(deduce((Base*)(0)));
        };
    }

    template <typename T>
    typename std::enable_if <Internal::isParsable <T>::value, void>::type
    xml_parse(T& value, std::string const& name, PropertyTree const& tree, XmlParseOptions const& options = {})
    {
        value.xml_parse(name, tree, options);
    }
}
