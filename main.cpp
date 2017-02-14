#include <iostream>

#include "mqtt/async_client.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    mqtt::async_client client({"tcp://192.168.1.248:1883"}, {"CLIENT"});

    mqtt::itoken_ptr conntok = client.connect();
    std::cout << "Waiting for the connection..." << std::flush;
    conntok->wait_for_completion();
    std::cout << "OK" << std::endl;


    std::cout << "Sending message..." << std::flush;
    mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>("coucou");
    pubmsg->set_qos(1);
    client.publish("home/cuve", pubmsg)->wait_for_completion(10);
    std::cout << "OK" << std::endl;

    return 0;
}