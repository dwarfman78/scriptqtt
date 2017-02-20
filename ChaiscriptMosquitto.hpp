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

#ifndef SCRIPTQTT_CHAISCRIPTMOSQUITTO_HPP
#define SCRIPTQTT_CHAISCRIPTMOSQUITTO_HPP

#include <mosquittopp.h>
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

#include "Message.hpp"
/*
 * Mosquittopp class that uses chaiscript scripts to handle incoming events (on_connect, on_message ...).
 *
 * Those scripts must exist under scripts/pDirPrefix/ and be named after the name of the event they're tied to.
 *
 * An instance of this object is accessible from within the scripts.
 *
 * Script name : 'mosquitto'
 *
 * Available methods from mosqpp::mosquittopp : 'connect' 'disconnect' and 'init' (reinitialize)
 */
class ChaiscriptMosquitto : public mosqpp::mosquittopp {

public:
    /*
     * Constructor.
     *
     * @param pChai : chaiscript interpretor.
     * @param pDirPrefix : name of the directory under which are stored the scripts.
     */
    ChaiscriptMosquitto(chaiscript::ChaiScript& pChai, const std::string& pDirPrefix);

    /*
     * Subscribe to a topic with a given qos.
     *
     * @param pTopic : topic to subscribe to.
     * @param pQos : Qos (0, 1 or 2)
     *
     * Script name : 'subscribe'
     */
    void subscribe(const std::string& pTopic, int pQos);

    /*
     * This method is called when mosquittopp is connected (after a call to mosquittopp::connect). It then call on_connect.chai to handle the connection.
     *
     * @param rc : Return code of the connection. (see libmosquitto documentation).
     */
    void on_connect(int rc);

    /*
     * This method is called when mosquittopp receives a message from any of its topic subscriptions.
     *
     * @param message : Message from the broker, the message is converted from mosquitto_message to Message class before it is given to the on_message.chai script.
     *                  The message object is named 'message' in the script.
     *
     */
    void on_message(const struct mosquitto_message *message);

    /*
     * This utility var is accessible from within scripts in order tell the runtime that the main loop can be stopped.
     *
     * Script name : 'continue'
     */
    bool shouldContinue;
private:
    /*
     * Chaiscript interpretor.
     */
    chaiscript::ChaiScript& mChai;

    /*
     * Directory name under which scripts are stored.
     */
    const std::string mDirPrefix{""};

};


#endif //SCRIPTQTT_CHAISCRIPTMOSQUITTO_HPP
