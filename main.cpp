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
#include <iostream>

#include "ChaiscriptMosquitto.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc == 2) {

        mosqpp::lib_init();

        // chaiscript interpretor.
        chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());

        // mosquittopp custom instance.
        ChaiscriptMosquitto cm(chai,std::string(argv[1]));

        // while we should continue..
        while(cm.shouldContinue) {

            // loop the mosquittopp instance
            // this method reads messages from subscriptions and calls callback methods
            // whenever a message arrives.
            cm.loop();
        }

        // disconnect from the broker. (this method can be called from scripts too)
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