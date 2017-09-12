#pragma once

namespace SXML
{
    struct XmlifyOptions
    {
        char attributeQuotes = '"';
        bool inArray = false;
        bool inObject = false;
        int inLineCounter = 0;
        bool noSpace = true;
    };
}
