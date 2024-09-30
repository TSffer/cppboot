#pragma once

#include <boost/asio.hpp>
#include <string>
#include <functional>
#include <unordered_map>
#include <memory>
#include "controller.hpp"

namespace cppboot
{
    namespace web
    {

        class Session : public std::enable_shared_from_this<Session>
        {
        public:
            Session(boost::asio::ip::tcp::socket socket, const std::unordered_map<std::string, std::unordered_map<std::string, HandlerFunction>>& routes);
            void start();

        private:
            void readRequest();
            void processRequest(std::size_t length);
            void sendResponse(const std::string &response);

            boost::asio::ip::tcp::socket socket_;
            const std::unordered_map<std::string, std::unordered_map<std::string, HandlerFunction>>& routes_;
            enum
            {
                max_length = 1024
            };
            char data_[max_length];
        };

        class Server
        {
            public:
                Server(int port);
                void start();
                void addRoute(const std::string& method, const std::string& path, HandlerFunction handler);
                
            private:
                void acceptConnection();

                boost::asio::io_context io_context_;
                boost::asio::ip::tcp::acceptor acceptor_;
                std::unordered_map<std::string, std::unordered_map<std::string, HandlerFunction>> routes_;        };

    } // namespace web
} // namespace cppboot