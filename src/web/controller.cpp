#include "cppboot/web/controller.hpp"

namespace cppboot
{
    namespace web
    {

        void Controller::addRoute(const std::string &method, const std::string &path, HandlerFunction handler)
        {
            routes_[method][path] = handler;
        }

        const std::unordered_map<std::string, std::unordered_map<std::string, HandlerFunction>> &Controller::getRoutes() const
        {
            return routes_;
        }

    } // namespace web
} // namespace cppboot