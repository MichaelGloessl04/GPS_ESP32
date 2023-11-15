#ifndef JSONHandler_h
#define JSONHandler_h

#include <ArduinoJson.h>

class JSONHandler {
  public:
    String newTimestamp(String client_name, String time, int team_id);
    int getTeam(String in_file, String mac);
    bool isSubstringPresent(String str, String substr);
  private:
    StaticJsonDocument<JSON_OBJECT_SIZE(3)> doc;
};

#endif