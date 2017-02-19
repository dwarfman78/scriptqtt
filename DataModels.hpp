#ifndef DATAMODELS_HPP
#define DATAMODELS_HPP
#include <mosquittopp.h>
struct Message
{
    Message(const std::string& pTopic, const std::string& pContent, int pQos, bool pRetained):mTopic(pTopic),mContent(pContent),mQos(pQos),mRetained(pRetained){;}

    void send(mosqpp::mosquittopp& pMosquitto){pMosquitto.publish(&mMessId,mTopic.c_str(),mContent.length(),mContent.c_str(),mQos,mRetained);}

    int mMessId;
    std::string mTopic, mContent;
    bool mRetained;
    int mQos;
};

#endif