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
#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <mosquittopp.h>
/*
 * This class represents a MQTT Message that can be received or sent.
 */
struct Message
{
    /*
     * Constructor to build a message to be sent to the broker.
     * This constructor can be called from a script to build a new message.
     * The message can be sent afterward through a call to 'send'.
     *
     * @param pTopic : topic to send message to.
     * @param pContent : content of the message.
     * @param pQos : Qos 0, 1 or 2.
     * @param pRetained : message retained, true or false.
     */
    Message(const std::string& pTopic, const std::string& pContent, int pQos, bool pRetained):mTopic(pTopic),mContent(pContent),mQos(pQos),mRetained(pRetained){;}

    /*
     * Constructor to build a received message from a mosquitto_message.
     * Converts a mosquitto_message and its content to a more c++ (and chaiscript) friendly format.
     *
     * @param message : mosquitto_message received to be converted.
     */
    Message(const mosquitto_message* message):mMessId(message->mid),mTopic(message->topic),mContent(static_cast<const char*>(message->payload)),mRetained(message->retain),mQos(message->qos){;}

    /*
     * Send (publish) the current message through the mosquittopp instance given as parameter.
     *
     * @param pMosquitto : mosquittopp instance to send message through. The instance must be connected and initialized.
     *
     * Script name : 'send'
     */
    void send(mosqpp::mosquittopp& pMosquitto){pMosquitto.publish(&mMessId,mTopic.c_str(),mContent.length(),mContent.c_str(),mQos,mRetained);}

    /*
     * Message id.
     *
     * Script name : 'id'
     */
    int mMessId;

    /*
     * Message topic and content received from or sent to.
     *
     * Script names : 'topic' and 'content'
     */
    std::string mTopic, mContent;

    /*
     * Message retained or not.
     */
    bool mRetained;

    /*
     * Message Qos.
     */
    int mQos;
};

#endif