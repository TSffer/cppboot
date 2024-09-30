#include "cppboot/core/application.hpp"
#include "cppboot/web/controller.hpp"
#include <memory>
#include <iostream>

CPPBOOT_CONTROLLER(HelloController);

void HelloController::registerRoutes() {
    addRoute("GET", "/hello", [](const cppboot::web::Request& req) {
        return cppboot::web::Response("Hello, CppBoot! (GET)");
    });

    addRoute("POST", "/hello", [](const cppboot::web::Request& req) {
        return cppboot::web::Response("Hello, CppBoot! (POST)\nReceived body: " + req.getBody());
    });

    addRoute("PUT", "/hello", [](const cppboot::web::Request& req) {
        return cppboot::web::Response("Hello, CppBoot! (PUT)\nReceived body: " + req.getBody());
    });

    addRoute("PATCH", "/hello", [](const cppboot::web::Request& req) {
        return cppboot::web::Response("Hello, CppBoot! (PATCH)\nReceived body: " + req.getBody());
    });

    addRoute("DELETE", "/hello", [](const cppboot::web::Request& req) {
        return cppboot::web::Response("Hello, CppBoot! (DELETE)");
    });
}

class MyApplication : public cppboot::core::Application {
public:
    MyApplication() {
        addController(std::make_shared<HelloController>());
    }
};

CPPBOOT_APPLICATION(MyApplication)