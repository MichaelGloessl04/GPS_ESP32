#ifndef JSONHandler_h
#define JSONHandler_h

#include <ArduinoJson.h>

class JSONHandler {
  public:
    void initJSON(const char* client_name);
    void newMsg();
    char* getMsg();
  private:
    StaticJsonDocument<1024> doc;
    JsonArray json_data;
    JsonObject json_entry;
};

#endif