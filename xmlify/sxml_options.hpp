#pragma once

namespace SXML
{
    struct XmlifyOptions
    {
        char attributeQuotes = '"';
        bool inArray = false;
        bool inObject = false;
        bool noSpace = true;
    };
}
