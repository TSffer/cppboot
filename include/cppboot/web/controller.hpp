#pragma once

#include <string>
#include <functional>
#include <unordered_map>

namespace cppboot
{
    namespace web
    {
        class Request {
            public:
                Request(const std::string &method, const std::string &path, const std::string &body) 
                    : method_(method), path_(path), body_(body) {}

                const std::string &getMethod() const { return method_; }
                const std::string &getPath() const { return path_; }
                const std::string &getBody() const { return body_; }
            
            private:
                std::string method_;
                std::string path_;
                std::string body_;
        };

        class Response {
            public:
                Response(const std::string &body, int statusCode = 200) 
                    : body_(body), statusCode_(statusCode) {}
                
                const std::string &getBody() const { return body_; }
                int getStatusCode() const { return statusCode_; }
            
            private:
                std::string body_;
                int statusCode_;
        };

        using HandlerFunction = std::function<Response(const Request &)>;

        class Controller
        {
            public:
                virtual ~Controller() = default;

                void addRoute(const std::string& method, const std::string& path, HandlerFunction handler);
                const std::unordered_map<std::string, std::unordered_map<std::string, HandlerFunction>>& getRoutes() const;
            protected:
                std::unordered_map<std::string, std::unordered_map<std::string, HandlerFunction>> routes_;
        };

    } // namespace web
} // namespace cppboot

#define CPPBOOT_CONTROLLER(ClassName)                 \
    class ClassName : public cppboot::web::Controller \
    {                                                 \
    public:                                           \
        ClassName()                                   \
        {                                             \
            registerRoutes();                         \
        }                                             \
                                                      \
    private:                                          \
        void registerRoutes();                        \
    }