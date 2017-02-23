/*Copyright (C) <2017> <Fabien LE CORRE (dwarf@dwarfman.fr)>
This software is provided 'as-is', without any express or implied
        warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
        including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
        in a product, an acknowledgment in the product documentation would be
        appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
        misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.*/
#include "ChaiscriptMosquitto.hpp"
ChaiscriptMosquitto::ChaiscriptMosquitto(chaiscript::ChaiScript& pChai,const std::string& pDirPrefix): mDirPrefix(pDirPrefix), mChai(pChai), shouldContinue(true)
{

    // init all chaiscript bindings
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mChai.add(chaiscript::base_class<mosqpp::mosquittopp, ChaiscriptMosquitto>());

    mChai.add(chaiscript::var(this), "mosquitto");
    mChai.add(chaiscript::fun(&ChaiscriptMosquitto::shouldContinue),"continue");

    mChai.add(chaiscript::fun<int, mosqpp::mosquittopp, const char *, int, int>(&mosqpp::mosquittopp::connect),
              "connect");
    mChai.add(chaiscript::fun(&mosqpp::mosquittopp::disconnect), "disconnect");
    mChai.add(chaiscript::fun(&mosqpp::mosquittopp::reinitialise), "init");
    mChai.add(chaiscript::fun<void,ChaiscriptMosquitto,const std::string&,int>(&ChaiscriptMosquitto::subscribe),"subscribe");

    mChai.add(chaiscript::user_type<Message>(), "Message");
    mChai.add(chaiscript::fun(&Message::mMessId),"id");
    mChai.add(chaiscript::fun(&Message::mContent),"content");
    mChai.add(chaiscript::fun(&Message::mTopic),"topic");
    mChai.add(chaiscript::constructor<Message(const std::string &pTopic, const std::string &pContent, int pQos,
                                                      bool pRetained)>(), "Message");
    mChai.add(chaiscript::fun(&Message::send), "send");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Call init scripts.
    mChai.eval_file("scripts/common/init.chai");
    mChai.eval_file("scripts/"+mDirPrefix+"/init.chai");

}
void ChaiscriptMosquitto::subscribe(const std::string& pTopic, int pQos)
{
    // Subscribe to the given topic.
    mosqpp::mosquittopp::subscribe(nullptr,pTopic.c_str(),pQos);
}
void ChaiscriptMosquitto::on_message(const struct mosquitto_message *message)
{
    // Create a Message from a mosquitto_message.
    Message mess = Message(message);

    // Bind the newly created message to the script.
    mChai.add(chaiscript::var(mess),"message");

    // Call the on_message script.
    mChai.eval_file("scripts/common/on_message.chai");
    mChai.eval_file("scripts/"+mDirPrefix+"/on_message.chai");

}
void ChaiscriptMosquitto::on_connect(int rc)
{
    if(rc == 0)
    {
        // if the connection is successful, call the on_connect script.
        mChai.eval_file("scripts/common/on_connect.chai");
        mChai.eval_file("scripts/" + mDirPrefix + "/on_connect.chai");
    }
    else
    {
        // otherwise well.. maybe we could try to reconnect.
        std::cerr << "Connection problem" <<std::endl;
    }
}
