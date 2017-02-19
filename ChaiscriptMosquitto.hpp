//
// Created by Fabien on 19/02/2017.
//

#ifndef SCRIPTQTT_CHAISCRIPTMOSQUITTO_HPP
#define SCRIPTQTT_CHAISCRIPTMOSQUITTO_HPP

#include <mosquittopp.h>
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

#include "DataModels.hpp"

class ChaiscriptMosquitto : public mosqpp::mosquittopp {

public:
    ChaiscriptMosquitto(chaiscript::ChaiScript& pChai, const std::string& pDirPrefix);
    void subscribe(const std::string& pTopic, int pQos);

    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);

    bool shouldContinue;
    //std::map<std::string,std::string> mSession;
private:
    chaiscript::ChaiScript& mChai;
    const std::string mDirPrefix{""};

};


#endif //SCRIPTQTT_CHAISCRIPTMOSQUITTO_HPP
