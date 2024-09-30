#pragma once

#include <string>
#include <vector>

namespace cppboot
{
    namespace data
    {

        template <typename T>
        class Repository
        {
        public:
            virtual void save(const T &entity) = 0;
            virtual T findById(int id) = 0;
            virtual std::vector<T> findAll() = 0;
            // Otros métodos...
        };

#define CPPBOOT_REPOSITORY(ClassName, EntityType)                  \
    class ClassName : public cppboot::data::Repository<EntityType> \
    {                                                              \
    public:                                                        \
        void save(const EntityType &entity) override;              \
        EntityType findById(int id) override;                      \
        std::vector<EntityType> findAll() override;                \
    };

    } 
} 