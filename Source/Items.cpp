#include <utility>

#include <utility>

//
// Created by kristian on 11/7/2018.
//

#include "Items.h"

void Items::item(int room, std::string n, int uses)
{
    item_room = room;
    name = std::move(n);
    health = uses;
}
bool Items::isActive() {return active;}
bool Items::isInInventory() {return in_inventory;}
bool Items::isVisible() {return visible;}
bool Items::isSpecial() {return special;}
int Items::getHealth() {return health;}
int Items::getItemRoom() {return item_room;}
void Items::setActive(bool in) {active = in;}
void Items::setInInventory(bool in) {in_inventory = in;}
void Items::setVisibe(bool in) {visible = in;}
void Items::setHealth(int in) {health = in;}
void Items::setItemRoom(int in) {item_room =in;}
void Items::setName(std::string in) {name = std::move(in);}
void Items::setSpecial(bool in) {special = in;}
std::string Items::getName() {return name;}
