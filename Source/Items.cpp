#include <utility>

#include <utility>

//
// Created by kristian on 11/7/2018.
//

#include "Items.h"

void Items::item(int room, std::string n,bool vis, bool get)
{
    item_room = room;
    name = std::move(n);
    visible = vis;
    is_gettable = get;
}
bool Items::isInInventory() {return in_inventory;}
bool Items::isVisible() {return visible;}
int Items::getItemRoom() {return item_room;}
void Items::setInInventory(bool in) {in_inventory = in;}
void Items::setVisibe(bool in) {visible = in;}
void Items::setItemRoom(int in) {item_room =in;}
void Items::setName(std::string in) {name = std::move(in);}
std::string Items::getName() {return name;}
bool Items::isGettable(){return is_gettable; }
