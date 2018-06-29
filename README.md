# SimpleXML
A project that follows the spirit of SimpleJSON, but for XML!

## Preface
Please submit pull requests if you don't agree with some behavior or found a bug, I would appreciate it.

This library can parse and serialize data from and to XML. It supports the most important STL containers and classes.
With the STL as a basis it is an easy to extend mechanism using structs. Use boost fusion and the provided utility
(see example below) or provide your own parse/stringify methods.

NOTE: The performance of this library is mostly influenced by boost property tree which is used for parsing XML.
Generating XML should be fast and well optimizable by the compiler.

Dependencies:
> boost/property_tree <br>
> boost/fusion <br>
> boost/mpl <br>

## Example (Basic Usage)
```C++
#include <SimpleXML/xml_parse/xml_parse.hpp>
#include <SimpleXML/xmlify/xmlify.hpp>

#include <vector>
#include <string>
#include <sstream>

struct Config
	: public SXML::Xmlifiable <Config>
	, public SXML::Parsable <Config>
{
	int a = 3;
	std::string b = "Hello";
	std::vector <std::string> c = {{}};
};

BOOST_FUSION_ADAPT_STRUCT
(
    Config,
    a, b, c
)

int main()
{
    std::stringstream sstr;
    sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"; // the library does not do this automatically, by choice.
    SXML::xmlify(sstr, "root_node", Config{});

    std::cout << sstr.str() << "\n";

    Config copy;
    SXML::xml_parse(copy, "root_node", SXML::parse_xml(sstr) /* creates boost property tree */);
}

```

## Example (Attributes)
```C++
#include <SimpleXML/xml_parse/xml_parse.hpp>
#include <SimpleXML/xmlify/xmlify.hpp>

// NEW!
#include <SimpleXML/utility/sxml_attribute.hpp>

struct A
	: public SXML::Xmlifiable <A>
	, public SXML::Parsable <A>
{
    SXML::Attribute <int> id;
};
BOOST_FUSION_ADAPT_STRUCT(A, id)

int main()
{
    SXML::xmlify(std::cout, "root_node", A{});
    // -> <root_node id="0"/>
}
``` 

## Example (Renaming)
This is useful for XML files that have element names that cannot be expressed as C++ identifiers.
Such praxis should be questioned anyway.
```C++
#include <SimpleXML/xml_parse/xml_parse.hpp>
#include <SimpleXML/xmlify/xmlify.hpp>

// NEW!
#include <SimpleXML/utility/sxml_rename.hpp>

struct A
	: public SXML::Xmlifiable <A>
	, public SXML::Parsable <A>
{
    SXML::Rename <std::string, SXML_SHORT_STRING("__weird_name")> goodName{"Hello"};

    A() {}
};
BOOST_FUSION_ADAPT_STRUCT(A, goodName)

int main()
{
    SXML::xmlify(std::cout, "root_node", A{});
    // -> <root_node><__weird_name>Hello</__weird_name></root_node>
}

```

## Example (Inlining) EXPERIMENTAL!
Inlines a member of a struct directly into the struct.
This is especially useful for XML files that have bad structuring, but you dont want to adapt your code to the bad external XML format.
```C++
#include <SimpleXML/xml_parse/xml_parse.hpp>
#include <SimpleXML/xmlify/xmlify.hpp>

// NEW!
#include <SimpleXML/utility/sxml_attribute.hpp>

struct B
	: public SXML::Xmlifiable <B>
	, public SXML::Parsable <B>
{
    std::string inlineMeToA = "Hello";
};
BOOST_FUSION_ADAPT_STRUCT(B, inlineMeToA)

struct A
	: public SXML::Xmlifiable <A>
	, public SXML::Parsable <A>
{
    SXML::Inline <B> NAME_IS_NOT_SIGNIFICANT_FOR_OUTPUT;
};
BOOST_FUSION_ADAPT_STRUCT(A, NAME_IS_NOT_SIGNIFICANT_FOR_OUTPUT)

int main()
{
    SXML::xmlify(std::cout, "root_node", A{});
    // -> <root_node><inlineMeToA>Hello</inlineMeToA></root_node>
}
```
