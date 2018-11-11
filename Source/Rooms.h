//
// Created by k2-bakov on 01/11/2018.
//

#ifndef BASICREB0RN_ROOMS_H
#define BASICREB0RN_ROOMS_H

#include <string>
#include <cstring>

class Rooms {

public:

    void room(bool n, bool s, bool e, bool w, bool u, bool d, std::string name, std::string desc, bool i);
    bool getNorth();
    bool getSouth();
    bool getWest();
    bool getEast();
    bool getUp();
    bool getDown();
    bool getItems();
    std::string getName();
    std::string getDesc();
    void setNorth(bool in);
    void setSouth(bool in);
    void setEast(bool in);
    void setWest(bool in);

private:

    bool north = false;
    bool south = false;
    bool east = false;
    bool west = false;
    bool up = false;
    bool down = false;
    bool has_item = false;
    std::string desc;
    std::string name;
    bool is_current_location = false;

};


#endif //BASICREB0RN_ROOMS_H
