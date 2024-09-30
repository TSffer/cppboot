#pragma once

#include <unordered_map>
#include <memory>
#include <typeindex>

namespace cppboot {
    namespace core {
        class Container {
            public:
                template<typename T>
                void registerComponent(std::shared_ptr<T> component);

                template<typename T>
                std::shared_ptr<T> getComponent();
            private:
                std::unordered_map<std::type_index, std::shared_ptr<void>> components_;
        };
    }    
}