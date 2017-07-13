#pragma once

namespace SXML
{
    struct XmlifyOptions
    {
        char attributeQuotes = '"';
        bool inArray = false;
        bool inObject = false;
        bool inLine = false;
        bool noSpace = true;
    };
}
