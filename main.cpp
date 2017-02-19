#include <iostream>

#include <chaiscript/chaiscript.hpp>

#include <chaiscript/chaiscript_stdlib.hpp>

#include "DataModels.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc == 2) {


        chaiscript::ChaiScript mChai(chaiscript::Std_Lib::library());

        mosqpp::mosquittopp mosquitto("CLIENT", true);

        mChai.add(chaiscript::var(&mosquitto), "mosquitto");

        mChai.add(chaiscript::user_type<Message>(), "Message");
        mChai.add(chaiscript::constructor<Message(const std::string &pTopic, const std::string &pContent, int pQos,
                                                  bool pRetained)>(), "Message");
        mChai.add(chaiscript::fun(&Message::send), "send");
        mChai.add(chaiscript::fun(&Message::mMessId),"id");

        mChai.add(chaiscript::fun<int, mosqpp::mosquittopp, const char *, int, int>(&mosqpp::mosquittopp::connect),
                  "connect");
        mChai.add(chaiscript::fun(&mosqpp::mosquittopp::disconnect), "disconnect");
        mChai.add(chaiscript::fun(&mosqpp::mosquittopp::reinitialise), "init");

        mChai.eval_file(argv[1]);

        return 0;
    }
    else
    {
        std::cerr << "Invalid argument, should be : scriptqtt 'scriptname' ";
    }
}