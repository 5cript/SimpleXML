#pragma once

#include <cstddef>

namespace SXML
{
    template <typename Base, typename ConversionPolicy>
    class MixinHelper : public Base
    {
    public:
        // using dynamic allocated polymorphism with this class would cause leaks.
        void* operator new(std::size_t) = delete;
        void* operator new[](std::size_t) = delete;
        void operator delete(void*) = delete;
        void operator delete[](void*) = delete;

    private:
        ConversionPolicy sxmlHandler = ConversionPolicy {this};
    };
}
