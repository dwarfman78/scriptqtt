#include <iostream>

#include "ChaiscriptMosquitto.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc == 2) {

        mosqpp::lib_init();

        chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());
        ChaiscriptMosquitto cm(chai,std::string(argv[1]));

        while(cm.shouldContinue) {
            cm.loop(1000,1);
        }

        cm.disconnect();

        mosqpp::lib_cleanup();

        return 0;
    }
    else
    {
        std::cerr << "Invalid argument, should be : scriptqtt 'scriptname' ";
        return -1;
    }
}