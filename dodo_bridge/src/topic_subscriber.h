#pragma once

#include "ros_client.h"
#include <json/json.h>
#include <string>
#include <functional>

class TopicSubscriber
{
public:
    TopicSubscriber(RosClient &client, const std::string &topic, const std::string &type);
    ~TopicSubscriber();

    void subscribe(std::function<void(const Json::Value &)> callback);
    void unsubscribe();
    void handle_message(const Json::Value &message);

private:

    RosClient &client_;
    std::string topic_;
    std::string type_;
    std::string id_;
    std::function<void(const Json::Value &)> callback_;
    bool subscribed_;
};