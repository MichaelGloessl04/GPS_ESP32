#include <ArduinoJson.h>
#include <JSONHandler.h>

const char* JSONHandler::newTimestamp(const char* client_name, int time, int team_id) {
    String msg;
    this->doc.clear();
    this->doc["mac"] = client_name;
    this->doc["time"] = time;
    this->doc["team_id"] = team_id;
    
    serializeJson(this->doc, msg);
    return msg.c_str();
}
