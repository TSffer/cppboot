#include "cppboot/core/application.hpp"
#include <iostream>

namespace cppboot
{
    namespace core
    {

        Application::Application() : server_(std::make_unique<web::Server>(8080)) {}

        void Application::run(int port)
        {
            for (const auto &controller : controllers_)
            {
                for (const auto &[method, routes] : controller->getRoutes())
                {
                    for (const auto &[path, handler] : routes)
                    {
                        server_->addRoute(method, path, handler);
                    }
                }
            }
            std::cout << "Starting server on port " << port << std::endl;
            server_->start();
        }

        void Application::addController(std::shared_ptr<web::Controller> controller)
        {
            controllers_.push_back(controller);
        }

    } // namespace core
} // namespace cppboot