#ifndef JSONHandler_h
#define JSONHandler_h

#include <ArduinoJson.h>

class JSONHandler {
  public:
    const char* newTimestamp(const char* client_name, int time, int team_id);
    void getTeam(String teamJSON);
  private:
    StaticJsonDocument<JSON_OBJECT_SIZE(3)> doc;
};

#endif