#ifndef JSONHandler_h
#define JSONHandler_h

#include <ArduinoJson.h>

class JSONHandler {
  public:
    const char* newTimestamp(const char* client_name, String time, int team_id);
    int getTeam(String in_file, const char* mac);
  private:
    StaticJsonDocument<JSON_OBJECT_SIZE(3)> doc;
};

#endif