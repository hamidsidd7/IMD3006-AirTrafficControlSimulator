#include "ofMain.h"
#include "gameObject.h"

using namespace std;

class Runway : public gameObject
{
private:
    int id = 0;
    string status = "NULL"; // "available", "occupied", "under maintenance"

public:
    Runway(int id);
    void setStatus(const string newStatus);
    string getStatus();
    bool isAvailable();
};
