#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <json/json.h>
#include <functional>
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>

using client = websocketpp::client<websocketpp::config::asio>;
using message_ptr = websocketpp::config::asio::message_type::ptr;

// Forward declaration
class TopicSubscriber;

class RosClient
{
public:
    RosClient(const std::string &host, int port);
    ~RosClient();

    bool connect();
    void disconnect();
    void run();
    void stop();

    void send_message(const Json::Value &message);
    void set_message_handler(std::function<void(const Json::Value &)> handler);

    // Subscriber management
    void register_subscriber(TopicSubscriber* subscriber);
    void unregister_subscriber(TopicSubscriber* subscriber);

    bool is_connected() const { return connected_; }

private:
    void on_open(websocketpp::connection_hdl hdl);
    void on_close(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl hdl, message_ptr msg);
    void on_fail(websocketpp::connection_hdl hdl);

    client client_;
    std::string uri_;
    websocketpp::connection_hdl connection_;
    std::atomic<bool> connected_;
    std::atomic<bool> running_;
    std::thread worker_thread_;
    std::function<void(const Json::Value &)> message_handler_;
    Json::Reader json_reader_;
    
    // Subscriber management
    std::vector<TopicSubscriber*> subscribers_;
    std::mutex subscribers_mutex_;
};