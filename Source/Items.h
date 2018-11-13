//
// Created by kristian on 11/7/2018.
//

#ifndef BASICREB0RN_ITEMS_H
#define BASICREB0RN_ITEMS_H

#include <string>


class Items {
public:
    void item(int room,std::string name,bool vis, bool get);

    bool isGettable();
    bool isVisible();
    bool isInInventory();
    int getItemRoom();
    std::string getName();
    void setVisibe(bool in);
    void setInInventory(bool in);
    void setItemRoom(int in);
    void setName(std::string in);
private:
    bool visible = true;
    bool in_inventory = false;
    bool is_gettable = true;
    int item_room = 0;
    std::string name;

};

#endif //BASICREB0RN_ITEMS_H
