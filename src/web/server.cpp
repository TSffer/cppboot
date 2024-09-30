#include "cppboot/web/server.hpp"
#include <iostream>
#include <regex>
#include <thread>

namespace cppboot
{
    namespace web
    {

        Session::Session(boost::asio::ip::tcp::socket socket, const std::unordered_map<std::string, std::unordered_map<std::string, HandlerFunction>> &routes)
            : socket_(std::move(socket)), routes_(routes) {}

        void Session::start()
        {
            readRequest();
        }

        void Session::readRequest()
        {
            auto self(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                    [this, self](boost::system::error_code ec, std::size_t length)
                                    {
                                        if (!ec)
                                        {
                                            std::cout << "Received request:\n"
                                                      << std::string(data_, length) << std::endl;
                                            processRequest(length);
                                        }
                                        else
                                        {
                                            std::cerr << "Error reading request: " << ec.message() << std::endl;
                                        }
                                    });
        }

        void Session::processRequest(std::size_t length)
        {
            std::string requestStr(data_, length);
            std::regex requestLineRegex("(GET|POST|PUT|PATCH|DELETE) (.+) HTTP/1");
            std::smatch matches;

            if (std::regex_search(requestStr, matches, requestLineRegex))
            {
                std::string method = matches[1];
                std::string path = matches[2];
                std::string body = requestStr.substr(requestStr.find("\r\n\r\n") + 4);

                Request request(method, path, body);
                Response response("404 Not Found", 404);

                if (routes_.find(method) != routes_.end())
                {
                    auto &methodRoutes = routes_.at(method);
                    if (methodRoutes.find(path) != methodRoutes.end())
                    {
                        response = methodRoutes.at(path)(request);
                    }
                }

                sendResponse(response);
            }
            else
            {
                sendResponse(Response("400 Bad Request", 400));
            }
        }

        void Session::sendResponse(const Response &response)
        {
            auto self(shared_from_this());
            std::string statusLine = "HTTP/1.1 " + std::to_string(response.getStatusCode()) + " OK\r\n";
            std::string headers = "Content-Type: text/plain\r\nContent-Length: " + std::to_string(response.getBody().length()) + "\r\n\r\n";
            std::string fullResponse = statusLine + headers + response.getBody();

            boost::asio::async_write(socket_, boost::asio::buffer(fullResponse),
                                     [this, self](boost::system::error_code ec, std::size_t /*length*/)
                                     {
                                         if (ec)
                                         {
                                             std::cerr << "Error sending response: " << ec.message() << std::endl;
                                         }
                                         else
                                         {
                                             std::cout << "Response sent successfully" << std::endl;
                                         }
                                     });
        }

        Server::Server(int port)
            : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

        void Server::start()
        {
            std::cout << "Server starting on port " << acceptor_.local_endpoint().port() << std::endl;
            acceptConnection();
            io_context_.run();
        }

        void Server::addRoute(const std::string &method, const std::string &path, HandlerFunction handler)
        {
            routes_[method][path] = handler;
            std::cout << "Added route: " << method << " " << path << std::endl;
        }

        void Server::acceptConnection()
        {
            acceptor_.async_accept(
                [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
                {
                    if (!ec)
                    {
                        std::cout << "Accepted connection from " << socket.remote_endpoint() << std::endl;
                        std::make_shared<Session>(std::move(socket), routes_)->start();
                    }
                    else
                    {
                        std::cerr << "Error accepting connection: " << ec.message() << std::endl;
                    }
                    acceptConnection();
                });
        }

    } // namespace web
} // namespace cppboot