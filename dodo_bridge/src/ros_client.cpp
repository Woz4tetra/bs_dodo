#include "ros_client.h"
#include "topic_subscriber.h"
#include <iostream>
#include <chrono>
#include <algorithm>

RosClient::RosClient(const std::string &host, int port)
    : uri_("ws://" + host + ":" + std::to_string(port)), connected_(false), running_(false)
{

    // Set up client
    client_.set_access_channels(websocketpp::log::alevel::all);
    client_.clear_access_channels(websocketpp::log::alevel::frame_payload);
    client_.set_error_channels(websocketpp::log::elevel::all);

    client_.init_asio();

    // Set handlers
    client_.set_open_handler([this](websocketpp::connection_hdl hdl)
                             { this->on_open(hdl); });

    client_.set_close_handler([this](websocketpp::connection_hdl hdl)
                              { this->on_close(hdl); });

    client_.set_message_handler([this](websocketpp::connection_hdl hdl, message_ptr msg)
                                { this->on_message(hdl, msg); });

    client_.set_fail_handler([this](websocketpp::connection_hdl hdl)
                             { this->on_fail(hdl); });
}

RosClient::~RosClient()
{
    stop();
}

bool RosClient::connect()
{
    websocketpp::lib::error_code ec;
    client::connection_ptr con = client_.get_connection(uri_, ec);

    if (ec)
    {
        std::cerr << "Connection initialization error: " << ec.message() << std::endl;
        return false;
    }

    connection_ = con->get_handle();
    client_.connect(con);

    return true;
}

void RosClient::disconnect()
{
    if (connected_)
    {
        websocketpp::lib::error_code ec;
        client_.close(connection_, websocketpp::close::status::going_away, "", ec);
        if (ec)
        {
            std::cerr << "Disconnect error: " << ec.message() << std::endl;
        }
    }
}

void RosClient::run()
{
    running_ = true;
    worker_thread_ = std::thread([this]()
                                 { client_.run(); });
}

void RosClient::stop()
{
    if (running_)
    {
        running_ = false;
        disconnect();
        client_.stop();
        if (worker_thread_.joinable())
        {
            worker_thread_.join();
        }
    }
}

void RosClient::send_message(const Json::Value &message)
{
    if (!connected_)
    {
        std::cerr << "Cannot send message: not connected" << std::endl;
        return;
    }

    Json::StreamWriterBuilder builder;
    std::string message_str = Json::writeString(builder, message);

    websocketpp::lib::error_code ec;
    client_.send(connection_, message_str, websocketpp::frame::opcode::text, ec);

    if (ec)
    {
        std::cerr << "Send message error: " << ec.message() << std::endl;
    }
}

void RosClient::set_message_handler(std::function<void(const Json::Value &)> handler)
{
    message_handler_ = handler;
}

void RosClient::register_subscriber(TopicSubscriber* subscriber)
{
    std::lock_guard<std::mutex> lock(subscribers_mutex_);
    subscribers_.push_back(subscriber);
}

void RosClient::unregister_subscriber(TopicSubscriber* subscriber)
{
    std::lock_guard<std::mutex> lock(subscribers_mutex_);
    subscribers_.erase(
        std::remove(subscribers_.begin(), subscribers_.end(), subscriber),
        subscribers_.end()
    );
}

void RosClient::on_open(websocketpp::connection_hdl hdl)
{
    std::cout << "Connection opened" << std::endl;
    connected_ = true;
}

void RosClient::on_close(websocketpp::connection_hdl hdl)
{
    std::cout << "Connection closed" << std::endl;
    connected_ = false;
}

void RosClient::on_message(websocketpp::connection_hdl hdl, message_ptr msg)
{
    Json::Value root;
    if (json_reader_.parse(msg->get_payload(), root))
    {
        // First call the global message handler if set
        if (message_handler_)
        {
            message_handler_(root);
        }
        
        // Then distribute to all registered subscribers
        std::lock_guard<std::mutex> lock(subscribers_mutex_);
        for (TopicSubscriber* subscriber : subscribers_)
        {
            subscriber->handle_message(root);
        }
    }
    else
    {
        std::cerr << "Failed to parse JSON message" << std::endl;
    }
}

void RosClient::on_fail(websocketpp::connection_hdl hdl)
{
    std::cerr << "Connection failed" << std::endl;
    connected_ = false;
}