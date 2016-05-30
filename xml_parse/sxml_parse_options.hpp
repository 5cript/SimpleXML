#pragma once

namespace SXML
{
    enum class InvalidPropertyHandlingBehaviour : int
    {
        IgnoreAllError,
        Default,
        Tag,
        Throw
    };

    enum class InvalidPathHandlingBehaviour : int
    {
        IgnoreAllError,
        Default,
        Tag,
        Throw
    };


    struct XmlParseOptions
    {
        InvalidPropertyHandlingBehaviour invalidPropertyHandler = InvalidPropertyHandlingBehaviour::Throw;
        InvalidPathHandlingBehaviour invalidPathHandler = InvalidPathHandlingBehaviour::Throw;

        char attributeQuotes = '"';
        bool inArray = false;
        bool inObject = false;
    };
}
