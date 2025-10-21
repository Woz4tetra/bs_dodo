#include "topic_subscriber.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>

TopicSubscriber::TopicSubscriber(RosClient &client, const std::string &topic, const std::string &type)
    : client_(client), topic_(topic), type_(type), subscribed_(false)
{

    // Generate a unique ID for this subscriber
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000, 99999);
    id_ = "subscribe_" + topic + "_" + std::to_string(dis(gen));

    // Register this subscriber with the client
    client_.register_subscriber(this);
}

TopicSubscriber::~TopicSubscriber()
{
    unsubscribe();
    // Unregister this subscriber from the client
    client_.unregister_subscriber(this);
}

void TopicSubscriber::subscribe(std::function<void(const Json::Value &)> callback)
{
    if (subscribed_)
    {
        std::cerr << "Already subscribed to topic: " << topic_ << std::endl;
        return;
    }

    callback_ = callback;

    Json::Value subscribe_msg;
    subscribe_msg["op"] = "subscribe";
    subscribe_msg["id"] = id_;
    subscribe_msg["topic"] = topic_;
    subscribe_msg["type"] = type_;

    client_.send_message(subscribe_msg);
    subscribed_ = true;

    std::cout << "Subscribed to topic: " << topic_ << " with ID: " << id_ << std::endl;
}

void TopicSubscriber::unsubscribe()
{
    if (!subscribed_)
    {
        return;
    }

    Json::Value unsubscribe_msg;
    unsubscribe_msg["op"] = "unsubscribe";
    unsubscribe_msg["id"] = id_;
    unsubscribe_msg["topic"] = topic_;

    client_.send_message(unsubscribe_msg);
    subscribed_ = false;

    std::cout << "Unsubscribed from topic: " << topic_ << std::endl;
}

void TopicSubscriber::handle_message(const Json::Value &message)
{
    // Check if this message is for our subscription (by ID or topic)
    bool is_our_message = false;

    if (message.isMember("id") && message["id"].asString() == id_)
    {
        is_our_message = true;
    }
    else if (message.isMember("topic") && message["topic"].asString() == topic_)
    {
        is_our_message = true;
    }

    if (is_our_message && message.isMember("msg") && callback_)
    {
        callback_(message["msg"]);
    }
}