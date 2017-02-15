#include <iostream>

#include "mqtt/async_client.h"

#include <chaiscript/chaiscript.hpp>

#include <chaiscript/chaiscript_stdlib.hpp>

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    chaiscript::ChaiScript mChai;

    mqtt::async_client client({"tcp://192.168.1.248:1883"}, {"CLIENT"});

    mChai.add(chaiscript::var(&client),"client");

    //chaiscript::fun<ReturnType (ParamType1, ParamType2)>(&function_with_overloads)
    //chaiscript::fun([this](const std::string& who, const std::string& something){ say(who,something); })

    //mChai.add(chaiscript::fun(&mqtt::async_client::connect,std::ref(client)),"connect");

    //mChai.add(chaiscript::base_class<mqtt::iasync_client, mqtt::async_client>());

    mChai.add(chaiscript::fun<mqtt::itoken_ptr,mqtt::async_client>(&mqtt::async_client::connect),"connect");

    mChai.add(chaiscript::fun<void,mqtt::itoken>(&mqtt::itoken::wait_for_completion),"wait_for_completion");
    //mChai.add(chaiscript::fun<mqtt::itoken_ptr (mqtt::async_client::*) ()>(&mqtt::async_client::connect),"connect");

    mChai.eval_file("scripts/connectMe.chai");


    /*mqtt::itoken_ptr conntok = client.connect();
    std::cout << "Waiting for the connection..." << std::flush;
    conntok->wait_for_completion();
    std::cout << "OK" << std::endl;*/


    std::cout << "Sending message..." << std::flush;
    mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>("coucou");
    pubmsg->set_qos(1);
    client.publish("home/cuve", pubmsg)->wait_for_completion(10);
    std::cout << "OK" << std::endl;

    return 0;
}