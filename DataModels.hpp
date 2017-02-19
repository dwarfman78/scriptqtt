#ifndef DATAMODELS_HPP
#define DATAMODELS_HPP
#include <mosquittopp.h>
struct Message
{
    Message(const mosquitto_message* message):mMessId(message->mid),mTopic(message->topic),mContent(static_cast<const char*>(message->payload)),mRetained(message->retain),mQos(message->qos){;}

    int mMessId;
    std::string mTopic, mContent;
    bool mRetained;
    int mQos;
};

#endif