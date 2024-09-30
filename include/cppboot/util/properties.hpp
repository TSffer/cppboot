#pragma once

#include <string>
#include <unordered_map>

namespace cppboot
{
    namespace util
    {

        class Properties
        {
        public:
            void load(const std::string &filename);
            std::string get(const std::string &key, const std::string &defaultValue = "");

        private:
            std::unordered_map<std::string, std::string> properties_;
        };

    }
}