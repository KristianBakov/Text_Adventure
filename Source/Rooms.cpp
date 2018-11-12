#include <utility>

#include <utility>

#include <utility>

//
// Created by k2-bakov on 01/11/2018.
//

#include "Rooms.h"
#include <string>

void Rooms::room(bool n, bool s, bool e, bool w, bool u, bool d, std::string na, std::string de, bool i,bool dark)
{
    north = n;
    south = s;
    west = w;
    east = e;
    up = u;
    down = d;
    name = std::move(na);
    desc = std::move(de);
    has_item = i;
    is_dark = dark;
}

bool Rooms::getNorth() { return north; }
bool Rooms::getSouth() { return south; }
bool Rooms::getWest() { return west; }
bool Rooms::getEast() { return east; }
bool Rooms::getUp() { return up; }
bool Rooms::getDown() { return down; }
bool Rooms::getItems() {return has_item;}
bool Rooms::isDark() {return is_dark;}
std::string Rooms::getName() { return name; }
std::string Rooms::getDesc() { return desc; }
void Rooms::setEast(bool in) {east = in;}
void Rooms::setNorth(bool in) {north = in;}
void Rooms::setSouth(bool in) {south = in;}
void Rooms::setWest(bool in) {west = in;}
void Rooms::setHasItem(bool in) {has_item = in;}
void Rooms::setDark(bool in) {is_dark = in;}
void Rooms::setName(std::string in) {name = in;}
void Rooms::setDesc(std::string in) {desc = in;}

