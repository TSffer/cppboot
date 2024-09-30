#pragma once

#include <memory>
#include <vector>
#include "../web/server.hpp"
#include "../web/controller.hpp"

namespace cppboot
{
    namespace core
    {

        class Application
        {
        public:
            Application();
            void run(int port = 8080);
            void addController(std::shared_ptr<web::Controller> controller);

        private:
            std::unique_ptr<web::Server> server_;
            std::vector<std::shared_ptr<web::Controller>> controllers_;
        };

    } // namespace core
} // namespace cppboot

#define CPPBOOT_APPLICATION(ClassName) \
    int main()                         \
    {                                  \
        ClassName app;                 \
        app.run();                     \
        return 0;                      \
    }