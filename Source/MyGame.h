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
    const float OBJ_X = 50;
    const float OBJ_Y = 60;
    const int STR_POS_X = 500;
    const int STR_POS_Y = 400;
	int current_room = 57;
    int increment = 100;
    GameObject specialItems[7];
	GameObject painting;
	GameObject ring;
	GameObject book;
	GameObject goblet;
	GameObject scroll;
	GameObject coins;
	GameObject statue;
	GameObject Candlestick;

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
    bool candle_lit = false;
    int candle_life = 45;
    int current_score = 0;

    static constexpr int ITEM_COUNT = 24;
	Items items[ITEM_COUNT];
	static constexpr int ROOM_COUNT = 64;
	Rooms room[ROOM_COUNT];
	std::string input;
	std::string current_verb = "";
	std::string current_noun;
	std::string current_desc;
	std::string input_copy;
	std::string feedback;
    std::size_t found_space = 0;
    static constexpr int VERB_COUNT = 26;

	std::string verb[VERB_COUNT] = {"","HELP","INVENTORY","GO","N","S","W","E","U","D","GET",
                         "TAKE","EXAMINE","OPEN","READ","SAY","DIG","SWING","CLIMB",
                         "LIGHT","UNLIGHT","SPRAY","USE","UNLOCK","LEAVE","SCORE"};
	static constexpr  int NOUN_COUNT = 31;
	std::string noun[NOUN_COUNT] = {"","PAINTING","RING","SPELLS","GOBLET","SCROLLS",
                         "COINS","STATUE","CANDLESTICK","MATCHES","VACUUM",
                         "BATTERIES","SHOVEL","AXE","ROPE","BOAT","AEROSOL","CANDLE",
                         "KEY","NORTH","SOUTH","WEST","EAST","UP","DOWN","DOOR","BATS",
                         "GHOSTS","DRAWER","DESK","COAT"};
	std::string exits;
	std::string item_string;
	std::string description;

	rect mouse_cursor;
};


#endif //HELLOASGE_MYGAME_H
