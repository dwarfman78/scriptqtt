#include <iostream>

#include <mosquittopp.h>

#include <chaiscript/chaiscript.hpp>

#include <chaiscript/chaiscript_stdlib.hpp>

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    chaiscript::ChaiScript mChai(chaiscript::Std_Lib::library());



    //mChai.add(chaiscript::var(&client),"client");

    //chaiscript::fun<ReturnType (ParamType1, ParamType2)>(&function_with_overloads)
    //chaiscript::fun([this](const std::string& who, const std::string& something){ say(who,something); })

    //mChai.add(chaiscript::fun(&mqtt::async_client::connect,std::ref(client)),"connect");

    //mChai.add(chaiscript::base_class<mqtt::iasync_client, mqtt::async_client>());

    //mChai.add(chaiscript::fun<mqtt::itoken_ptr,mqtt::async_client>(&mqtt::async_client::connect),"connect");

    //mChai.add(chaiscript::fun<void,mqtt::itoken>(&mqtt::itoken::wait_for_completion),"wait_for_completion");
    //mChai.add(chaiscript::fun<mqtt::itoken_ptr (mqtt::async_client::*) ()>(&mqtt::async_client::connect),"connect");

    //mChai.eval_file("scripts/connectMe.chai");

    mosqpp::mosquittopp mosquitto("CLIENT",true);

    mosquitto.connect("192.168.1.248");

    mosquitto.publish(nullptr,"home/cuve",1,"1",1,false);

    mosquitto.disconnect();

    return 0;
}