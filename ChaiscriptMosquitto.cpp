//
// Created by Fabien on 19/02/2017.
//

#include "ChaiscriptMosquitto.hpp"
ChaiscriptMosquitto::ChaiscriptMosquitto(chaiscript::ChaiScript& pChai,const std::string& pDirPrefix): mDirPrefix(pDirPrefix), mChai(pChai), shouldContinue(true)
{
   // mChai.add(chaiscript::bootstrap::standard_library::map_type<std::map<std::string, std::string> >("mapOfStrings"));

    mChai.add(chaiscript::base_class<mosqpp::mosquittopp, ChaiscriptMosquitto>());

    mChai.add(chaiscript::var(this), "mosquitto");
    mChai.add(chaiscript::fun(&ChaiscriptMosquitto::shouldContinue),"continue");
    //mChai.add(chaiscript::var(mSession),"session");

    mChai.add(chaiscript::fun<int, mosqpp::mosquittopp, const char *, int, int>(&mosqpp::mosquittopp::connect),
              "connect");
    mChai.add(chaiscript::fun(&mosqpp::mosquittopp::disconnect), "disconnect");
    mChai.add(chaiscript::fun(&mosqpp::mosquittopp::reinitialise), "init");
    mChai.add(chaiscript::fun<void,ChaiscriptMosquitto,const std::string&,int>(&ChaiscriptMosquitto::subscribe),"subscribe");

    mChai.add(chaiscript::user_type<Message>(), "Message");
    mChai.add(chaiscript::fun(&Message::mMessId),"id");
    mChai.add(chaiscript::fun(&Message::mContent),"content");
    mChai.add(chaiscript::fun(&Message::mTopic),"topic");


    mChai.eval_file("scripts/"+mDirPrefix+"/init.chai");

}
void ChaiscriptMosquitto::subscribe(const std::string& pTopic, int pQos)
{
    mosqpp::mosquittopp::subscribe(nullptr,pTopic.c_str(),pQos);
}
void ChaiscriptMosquitto::on_message(const struct mosquitto_message *message)
{
    Message mess = Message(message);

    mChai.add(chaiscript::var(mess),"message");

    mChai.eval_file("scripts/"+mDirPrefix+"/on_message.chai");

}
void ChaiscriptMosquitto::on_connect(int rc)
{
    if(rc == 0)
    {
        mChai.eval_file("scripts/" + mDirPrefix + "/on_connect.chai");
    }
    else
    {
        std::cerr << "Connection problem" <<std::endl;
    }
}
