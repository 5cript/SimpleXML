#pragma once

namespace SXML
{
    struct XmlifyOptions
    {
        bool noTags = false;
        char attributeQuotes = '"';

        XmlifyOptions withoutTags() const;
    };
}
