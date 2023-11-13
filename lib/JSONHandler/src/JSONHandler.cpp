#include <ArduinoJson.h>
#include <JSONHandler.h>

const char* JSONHandler::newTimestamp(const char* client_name, int time, int team_id) {
    String msg;
    const char* out_msg;
    this->doc.clear();
    this->doc["mac"] = client_name;
    this->doc["time"] = time;
    this->doc["team_id"] = team_id;
    
    serializeJson(this->doc, msg);
    out_msg = msg.c_str();
    return out_msg;
}

int JSONHandler::getTeam(String in_file, const char* mac) {
    const int capacity = JSON_OBJECT_SIZE(1000);
    DynamicJsonDocument doc(capacity);
    DeserializationError error = deserializeJson(doc, in_file);
    if (error) {
        Serial.print(error.c_str());
    }

    String macs = doc["macs"].as<String>();
    String team_id = doc["team_id"].as<String>();
    doc.clear();

    if (macs.indexOf(mac) >= 0) {
        return team_id.toInt();
    } else {
        return 0;
    }
}
