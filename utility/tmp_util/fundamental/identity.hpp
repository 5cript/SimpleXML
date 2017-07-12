#pragma once

namespace SXML {
    template <typename T>
    struct identity {
        using type = T;
    };

    struct identity_functor {
        template <typename T>
        struct apply {
            using type = T;
        };
    };
}
