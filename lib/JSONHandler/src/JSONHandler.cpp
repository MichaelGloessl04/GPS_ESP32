#include <ArduinoJson.h>
#include <JSONHandler.h>

void JSONHandler::initJSON(const char* client_name) {
    doc.clear();
    doc["client"] = client_name;
    json_data = doc.createNestedArray("measurements");
}

char* JSONHandler::getMsg(const char* client_name) {
    char* msg;
    serializeJson(doc, output);
    output = "{\"data\":" + output + "}";
    
    init_json(KEY);
    return msg;
}

char*