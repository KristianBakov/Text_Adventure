//
// Created by Huxy on 03/10/2018.
//

#ifndef HELLOASGE_MYGAME_H
#define HELLOASGE_MYGAME_H

#include <string>
#include <cstring>
#include <Engine/OGLGame.h>

#include "GameObject.h"
#include "Rect.h"
#include "Rooms.h"
#include "Items.h"

class MyGame : public ASGE::OGLGame
{
public:
	MyGame();
	virtual ~MyGame();
	bool init() override;
	void update(const ASGE::GameTime& us) override;
	void render(const ASGE::GameTime& us) override;
private:
    const int ROW = 8;
	int current_room = 57;

	void initializeRooms();
	void initializeItems();
	void keyHandler(const ASGE::SharedEventData data);
	void clickHandler(const ASGE::SharedEventData data);
	void setupResolution();
	void inputText(const ASGE::KeyEvent *key);
    void checkNoun(int v);
    void goEast();
    void goWest();
    void goSouth();
    void goNorth();
	int key_callback_id = -1;	        /**< Key Input Callback ID. */
	int  mouse_callback_id = -1;        /**< Mouse Input Callback ID. */

	bool enter_pressed = false;
	bool room_updated = true;
	bool is_paralyzed = false;
    bool found_verb = false;
    bool door_locked = true;
    bool magic_barrier = true;
    bool on_tree = false;

    static constexpr int ITEM_COUNT = 24;
	Items items[ITEM_COUNT];
	static constexpr int ROOM_COUNT = 64;
	Rooms room[ROOM_COUNT];
	std::string input;
	std::string current_verb = "";
	std::string current_noun;
	std::string input_copy;
	std::string feedback;
    std::size_t found_space = 0;
    static constexpr int VERB_COUNT = 26;

	std::string verb[VERB_COUNT] = {"","HELP","INVENTORY","GO","N","S","W","E","U","D","GET",
                         "TAKE","EXAMINE","OPEN","READ","SAY","DIG","SWING","CLIMB",
                         "LIGHT","UNLIGHT","SPRAY","USE","UNLOCK","LEAVE","SCORE"};
	std::string noun[31] = {"","PAINTING","RING","SPELLS","GOBLET","SCROLLS",
                         "COINS","STATUE","CANDLESTICK","MATCHES","VACUUM",
                         "BATTERIES","SHOVEL","AXE","ROPE","BOAT","AEROSOL","CANDLE",
                         "KEY","NORTH","SOUTH","WEST","EAST","UP","DOWN","DOOR","BATS",
                         "GHOSTS","DRAWER","DESK","COAT"};
	std::string exits;
	std::string item_string;
	std::string test;

	rect mouse_cursor;
};


#endif //HELLOASGE_MYGAME_H
