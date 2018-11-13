#include <utility>
//
// Haunted House Remastered by Kristian Bakov 13/11/18
//
#include <iostream>
#include <Engine\Renderer.h>
#include "GameObject.h"
#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Platform.h>
#include <Engine/Sprite.h>
#include <Engine/FileIO.h>
#include "MyGame.h"
#include "Rooms.h"
#include "Items.h"

MyGame::MyGame() = default;

MyGame::~MyGame()
{
	this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
	this->inputs->unregisterCallback(static_cast<unsigned int>(mouse_callback_id));
}
bool MyGame::init()
{
	setupResolution();
	if (!initAPI())
	{
		return false;
	}
	toggleFPS();


//    ASGE::FILEIO::File font;
//    font.open("/Resources/Fonts/retro.ttf", ASGE::FILEIO::File::IOMode::READ);
//    ASGE::FILEIO::IOBuffer buffer(font.read());
//    auto idx = renderer->loadFontFromMem("retro", buffer.as_unsigned_char(),buffer.length, 18);
//    renderer->setFont(idx);

for (int i = 1;i <19;i++)
{
	items[i].setInInventory(true);
	items[15].setInInventory(false);
}

	renderer->setWindowTitle("The Haunted House");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	initializeRooms();
	initializeItems();

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &MyGame::keyHandler, this);

	//mouse_callback_id = inputs->addCallbackFnc(
	//	ASGE::E_MOUSE_CLICK, &MyGame::clickHandler, this);


    if (!specialItems[0].addSpriteComponent(renderer.get(), "Resources/item0.png"))
    {
        return false;
    }
//	for (int i=0; i<7; i++)
//    {
//        if (!specialItems[i].addSpriteComponent(renderer.get(),
//                "Resources/item"+std::to_string(i)+".png")) {
//            return false;
//        }
//        specialItems[i].spriteComponent()->getSprite()->width(OBJ_X);
//        specialItems[i].spriteComponent()->getSprite()->height(OBJ_Y);
//        specialItems[i].spriteComponent()->getSprite()->xPos(STR_POS_X);
//        specialItems[i].spriteComponent()->getSprite()->yPos(STR_POS_Y);
//    }

	return true;
}
//set the current resolution. Please do nt change
void MyGame::setupResolution()
{
	game_width = 1024;
	game_height = 768;
}
//update for all 'go' verbs
void MyGame::goEast()
{
	if (!room[current_room + 1].isDark() ||
			(room[current_room + 1].isDark() && candle_lit
			&& candle_life > 0))
	{
		current_room += 1;
		input_copy.clear();
		room_updated = true;
		if (candle_lit)
		{
			candle_life--;
		}
	}
	else if (room[current_room + 1].isDark() && !candle_lit)
	{
		feedback.assign("THE ROOM TO THE EAST IS TOO DARK TO ENTER");
	}
}
void MyGame::goWest()
{
	if (!room[current_room - 1].isDark() ||
		(room[current_room - 1].isDark() && candle_lit
		&& candle_life > 0))
	{
		current_room -= 1;
		input_copy.clear();
		room_updated = true;
		if (candle_lit)
		{
			candle_life--;
		}
	}
	else if (room[current_room - 1].isDark() && !candle_lit)
	{
		feedback.assign("THE ROOM TO THE WEST IS TOO DARK TO ENTER");
	}
}
void MyGame::goNorth()
{
	if (!room[current_room - ROW].isDark() ||
		(room[current_room - ROW].isDark() && candle_lit
		&& candle_life > 0))
	{
		current_room -= ROW;
		input_copy.clear();
		room_updated = true;
		if (candle_lit)
		{
			candle_life--;
		}
        if (current_room == 41)
        {
            room[current_room].setDesc("You have entered the house.\n The door behind you has shut.");
            room[41].setSouth(false);
            room[49].setNorth(false);
        }
	}
	else if (room[current_room - ROW].isDark() && !candle_lit)
	{
		feedback.assign("THE ROOM TO THE NORTH IS TOO DARK TO ENTER");
	}
}
void MyGame::goSouth()
{
	if (!room[current_room + ROW].isDark() ||
		(room[current_room + ROW].isDark() && candle_lit
		&& candle_life > 0))
	{
		current_room += ROW;
		input_copy.clear();
		room_updated = true;
		if (candle_lit)
		{
			candle_life--;
		}
	}
	else if (room[current_room + ROW].isDark() && !candle_lit)
	{
		feedback.assign("THE ROOM TO THE SOUTH IS TOO DARK TO ENTER");
	}
}
void MyGame::initializeItems()
{
    items[1].item(46,noun[1],true,true); // painting
    items[2].item(38,noun[2],false,true); // ring
    items[3].item(35,noun[3],true,true); //book of spells
    items[4].item(50,noun[4],true,true); //goblet
    items[5].item(13,noun[5],true,true); //scroll
    items[6].item(18,noun[6],true,true); // coins
    items[7].item(28,noun[7],true,true); //statue
    items[8].item(42,noun[8],true,true); //candlestick
    items[9].item(10,noun[9],true,true); // matches
    items[10].item(25,noun[10],true,true); // vacuum
    items[11].item(26,noun[11],true,true); // batteries
    items[12].item(4,noun[12],true,true); //shovel
    items[13].item(2,noun[13],true,true); //axe
    items[14].item(7,noun[14],true,true); //rope
    items[15].item(47,noun[15],true,true); //boat
    items[16].item(60,noun[16],true,true); //aerosol
    items[17].item(43,noun[17],false,true); //candle
    items[18].item(32,noun[18],false,true); //key
    items[19].item(13,noun[26],true, false); //bats
    items[20].item(52,noun[27],true, false);//ghosts
    items[21].item(43,noun[28],false, false); //drawer
    items[22].item(43,noun[29],false, false); //desk
	items[23].item(32,noun[30],false, false); //coat

}
void MyGame::initializeRooms()
{
    room[0].room(false,true,true,false,false,false,"Dark corner",
            "The shadow of the house\n falls upon this corner.",
            false,false);
    room[1].room(false,false,true,true,false,false,"Overgrown Garden",
            "There are only withering thorns around.\n "
            "You can't see anything of use.", false,false);
    room[2].room(false,false,true,true,false,false,"By Woodpile",
            "There is some freshly cut wood.",true,false);
    room[3].room(false,true,true,true,false,false,"Rubbish Yard",
            "There is a pile of rubbish on the ground.",
            false,false);
    room[4].room(false,false,true,true,false,false,"Weedpatch",
            "Something has allowed a large number of\n"
            " weeds to grow here.", true,false);
    room[5].room(false,false,true,true,false,false,"Forest",
            "There are trees all around you.",false,false);
    room[6].room(false,true,true,true,false,false,"Thick Forest",
            "The Forest thickens, and it is hard to see.",
            false,false);
    room[7].room(false,true,false,true,false,false,"Blasted Tree",
            "This single tree seems to have been struck\n"
            " by lightning.",true,false);
    room[8].room(true,true,false,false,false,false,"Corner of the House",
            "You can barely pass through this tiny gap.",
            false,false);
    room[9].room(false,true,true,false,false,false,
            "Entrance to the Kitchen",
            "You can see a kitchen to the east.",false,false);
    room[10].room(false,false,true,true,false,false,"Kitchen",
            "There are broken plates all around.",true,false);
    room[11].room(true,false,false,true,false,false,"Scullery door",
            "A room with door made out of ivory...\n or bones.",
            false,false);
    room[12].room(false,true,true,false,false,false,"Dusty room",
            "There are few inches of dust covering all\n"
            " surfaces in this room.",false,true);
    room[13].room(false,false,false,true,false,false,"Rear turret room",
            "A dark room with no window to the outside.", true, true);
    room[14].room(true,false,true,false,false,false,"Clearing",
            "There is a path leading to the forest.",false,false);
    room[15].room(true,true,false,true,false,false,"Cobblstone Path",
            "A very rocky area.",false,false);
    room[16].room(true,true,false,false,false,false,"Side of House",
            "There is a window but you\n cannot see through.",false,false);
    room[17].room(true,true,false,false,false,false,"Back of hallway",
            "Doesn't seem like there is \nanything of interest here.",false,false);
    room[18].room(false,true,true,false,false,false,"Dark Alcove",
            "You can barely see even with \nyour candle lit.", true,true);
    room[19].room(false,false,true,true,false,false,"Small Dark Room",
            "You can see a staircase.",false, true);
    room[20].room(true,false,false,true,true,true,"Spiral Staircase",
            "The staircase leads to the second floor.",false, true);
    room[21].room(false,true,true,false,false,false,"Wide Passage",
            "Doesn't seem like there is anything\n of interest here.",false,true);
    room[22].room(false,true,false,true,true,true,"Slippery stairs",
            "There is water leaking.",false, true);
    room[23].room(true,true,false,false,false,false,"Clifftop",
            "A mountainous area.",false,false);
    room[24].room(true,false,false,false,false,false,"Crumbling Wall",
            "The wall is barely standing.",false,false);
    room[25].room(true,true,false,false,false,false,"Gloomy Passage",
            "A spooky corridor with creepy\n paintings on the walls.", true,false);
    room[26].room(true,true,true,false,false,false,"Pool of Light",
            "Looks like there are no light\n sources ahead.",true,false);
    room[27].room(false,false,true,true,false,false,"Impressive Vaulted Hall",
            "The room is decorated with\n items of value.",false,true);
    room[28].room(false,false,true,true,false,false,"Hall with Thick Wooden Door",
            "A passage with a locked door.",true,true);
    room[29].room(true,true,false,true,false,false,"Trophy Room",
            "There are wooden trophies on the walls.",false,true);
    room[30].room(true,true,false,false,false,false,"Cellar with Iron Bars",
            "You can see rays of light coming\n trough the iron bar window.",false,true);
    room[31].room(true,true,false,false,false,false,"Cliff Path (North)",
            "Doesn't seem like there is anything\n of interest here.",false,false);
    room[32].room(false,true,false,false,false,false,"Cupboard with a Hanging Coat",
            "You are inside a ridiculously huge\n cupboard. There is a coat.", true,false);
    room[33].room(true,true,true,false,false,false,"Front Hall",
            "A wide room leading to multiple rooms.",false,false);
    room[34].room(true,true,false,true,false,false,"Sitting Room",
            "There is a comfy couch at the other\n end of the room.",false,false);
    room[35].room(false,true,false,false,false,false,"Secret Room",
            "This room was strategically hidden?",true,false);
    room[36].room(true,true,false,false,true,true,"Steep Marble Steps",
            "These steps are dangerous! \n"
            "You decide to walk very carefully.",false,true);
    room[37].room(true,false,false,false,false,false,"Dining Room",
            "Doesn't seem like there is anything\n of interest here.",false,false);
    room[38].room(true,false,false,false,false,false,"Deep Cellar with Coffin",
            "A very creepy room. It smells bad.",true,true);
    room[39].room(true,true,false,false,false,false,"Cliff Path (South)",
            "Doesn't seem like there is anything\n of interest here.",false,false);
    room[40].room(true,false,true,false,false,false,"Closet",
            "Clothes. Clothes. Clothes.",false,false);
    room[41].room(true,true,false,true,false,false,"Front Lobby",
            "You entered the house.",false,false);
    room[42].room(true,false,true,false,false,false,"Library with Evil Books",
            "There are shelves full of books.\n "
            "You can hear strange noises coming from them.",true,false);
    room[43].room(false,false,false,true,false,false,"Study with a Desk & Hole in the Wall",
            "There is a small hole in the wall.\n Light comes through.",
            true,false);
    room[44].room(true,true,true,false,false,false,"Cobwebby Room",
            "It's full of webs! You can hear disturbing\n noises all"
            " around you.",false,true);
    room[45].room(false,false,true,true,false,false,"Cold Chamber",
            "It feels like this room is not part of\n the house, it's freezing!",
            false,true);
    room[46].room(false,false,false,true,false,false,"Spooky Room",
            "Doesn't seem like there is anything of\n interest here.",
            true,true);
    room[47].room(true,true,false,false,false,false,"Cliff Path by Marsh",
            "The waters here are deep.",
            true,false);
    room[48].room(false,true,true,false,false,false,"Verandah",
            "You are standing on the front verandah.\n"
            " You try to peek in but it's too dark.",false,false);
	room[49].room(true, true, false, true, false, false, "Front Porch",
	        "You are standing in front of the main\n entrance to the house.",
	        false,false);
	room[50].room(false,false,true,false,false,false,"Front Tower",
	        "A room full of treasures.", true,false);
	room[51].room(false,false,true,true,false,false,"Slopping Corridor",
	        "Doesn't seem like there is anything\n of interest here.",false,false);
	room[52].room(true,false,false,true,false,false,"Upper Gallery",
	        "This room gives you the chills.",false,false);
	room[53].room(false,true,false,false,false,false,"Marsh by Wall",
	        "Doesn't seem like there is anything\n of interest here.",false,false);
	room[54].room(false,true,false,true,false,false,"Marsh",
	        "You are stuck!",false,false);
	room[55].room(true,false,false,true,false,false,"Soggy Path",
	        "The ground is so wet your shoes get\n are all muddy.",false,false);
	room[56].room(true,false,true,false,false,false,"By Twisted Railing",
	        "Doesn't seem like there is anything\n to the west.",false,false);
	room[57].room(true, false, true, true, false, false, "Path Through Iron Gate",
	        "There is a big iron gate behind you.",false,false);
	room[58].room(false, false, true, true, false, false, "Path by railings",
	        "Doesn't seem like there is anything\n of interest here.",false,false);
	room[59].room(false, false, true, true, false, false,"Beneath Front Tower",
	        "There is a very fancy looking room\n on the second floor above.",false,false);
	room[60].room(false, false, true, true, false, false,"Debris from Crumbling Facade",
	        "Part of the wall has crumbled.",true,false);
	room[61].room(true, false, true, true, false, false,"Large Fallen Brickwork",
	        "Seems like it has been abandoned\n for a while.",false,false);
	room[62].room(true, false, true, true, false, false,"Rotting Stone Arch",
	        "There is a single arch that has\n been overgrown by weeds.",false,false);
	room[63].room(false, false, false, true, false, false,"Crumbling Clifftop",
	        "There is a hill to the north.\n You try to climb but it's too steep.",false,false);
}


void MyGame::keyHandler(const ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent *>(data.get());
	inputText(key);
	if (key->key == ASGE::KEYS::KEY_ENTER &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input_copy.assign(input);
		input.clear();
		enter_pressed = true;
	}
	if (key->key == ASGE::KEYS::KEY_ENTER &&key->action == ASGE::KEYS::KEY_RELEASED)
	{
		enter_pressed = false;
}
}

void MyGame::clickHandler(const ASGE::SharedEventData data)
{
	auto click = static_cast<const ASGE::ClickEvent *>(data.get());
	double x_pos, y_pos;
	inputs->getCursorPos(x_pos, y_pos);
	mouse_cursor.x = static_cast<float>(x_pos);
	mouse_cursor.y = static_cast<float>(y_pos);

	if (click->button == 0 && click->action == 1)
	{
		signalExit();
	}
}
void MyGame::inputText(const ASGE::KeyEvent *key) {
	if(key->key == ASGE::KEYS::KEY_A &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('A');
	}
	if(key->key == ASGE::KEYS::KEY_B &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('B');
	}
	if(key->key == ASGE::KEYS::KEY_C &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('C');
	}
	if(key->key == ASGE::KEYS::KEY_D &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('D');
	}
	if(key->key == ASGE::KEYS::KEY_E &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('E');
	}
	if(key->key == ASGE::KEYS::KEY_F &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('F');
	}
	if(key->key == ASGE::KEYS::KEY_G &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('G');
	}
	if(key->key == ASGE::KEYS::KEY_H &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('H');
	}
	if(key->key == ASGE::KEYS::KEY_I &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('I');
	}
	if(key->key == ASGE::KEYS::KEY_J &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('J');
	}
	if(key->key == ASGE::KEYS::KEY_K &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('K');
	}
	if(key->key == ASGE::KEYS::KEY_L &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('L');
	}
	if(key->key == ASGE::KEYS::KEY_M &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('M');
	}
	if(key->key == ASGE::KEYS::KEY_N &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('N');
	}
	if(key->key == ASGE::KEYS::KEY_O &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('O');
	}
	if(key->key == ASGE::KEYS::KEY_P &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('P');
	}
	if(key->key == ASGE::KEYS::KEY_Q &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('Q');
	}
	if(key->key == ASGE::KEYS::KEY_R &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('R');
	}
	if(key->key == ASGE::KEYS::KEY_S &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('S');
	}
	if(key->key == ASGE::KEYS::KEY_T &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('T');
	}
	if(key->key == ASGE::KEYS::KEY_U &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('U');
	}
	if(key->key == ASGE::KEYS::KEY_V &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('V');
	}
	if(key->key == ASGE::KEYS::KEY_W &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('W');
	}
	if(key->key == ASGE::KEYS::KEY_X &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('X');
	}
	if(key->key == ASGE::KEYS::KEY_Y &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('Y');
	}
	if(key->key == ASGE::KEYS::KEY_Z &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('Z');
	}
	if(key->key == ASGE::KEYS::KEY_SPACE &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back(' ');
	}
    if(key->key == ASGE::KEYS::KEY_BACKSPACE &&key->action == ASGE::KEYS::KEY_PRESSED && input.length() > 0)
    {
        input.pop_back();
    }
}
void MyGame::checkNoun(int v)
{
	// v represents verb number from the verb string.
	// It is being checked and matched to the appropriate nouns;
	// sets default msg for feedback string;
	if (v == 0)
	{
		feedback.assign("WHAT WILL YOU DO NEXT?");
	}
	//Render available commands
	else if (v == 1)
	{
		item_string.clear();
		feedback.clear();
		for (int i=1;i<VERB_COUNT;i++)
		{
			feedback.append(verb[i] + ",");
			if (i % 6 == 0)
			{
				feedback.append("\n");
			}
		}
		std::size_t last_comma = feedback.find_last_of(',');
		feedback.erase(last_comma);
	}
	//Items being carried - INVENTORY
	else if (v == 2)
	{
		feedback.clear();
		item_string.clear();
		for (int i=0;i<ITEM_COUNT;i++)
		{
			if (items[i].isInInventory())
			{
				feedback.append(items[i].getName() + ", ");
				if (i % 6 == 0)
				{
					feedback.append("\n");
				}
			}
		}
	}
	//Moving around the grid;
	else if (((v == 3 && current_noun == noun[22]) || v == 7))
    {
            if (room[current_room].getEast() && !is_paralyzed)
            {
                goEast();
            }
            else if (!room[current_room].getEast())
            {
                feedback.assign("CAN'T GO FURTHER EAST!");
            }
    }
	else if (((v == 3 && current_noun == noun[21]) || v == 6))
	{
	    if (room[current_room].getWest() && !is_paralyzed)
	    {
            goWest();
        }
        else if (!room[current_room].getWest())
        {
            feedback.assign("CAN'T GO FURTHER WEST!");
        }
	}
	else if (((v == 3 && current_noun == noun[20]) || v == 5))
	{
	    if (room[current_room].getSouth() && !is_paralyzed)
	    {
            goSouth();
        }
        else if (!room[current_room].getSouth())
        {
            feedback.assign("CAN'T GO FURTHER SOUTH!");
        }
	}
	else if (((v == 3 && current_noun == noun[19]) || v == 4))
	{
	    if (room[current_room].getNorth() && !is_paralyzed)
	    {
            goNorth();
        }
        else if (!room[current_room].getNorth())
        {
            feedback.assign("CAN'T GO FURTHER NORTH!");
        }
	}
	else if (((v == 3 && current_noun == noun[23]) || v == 8))
    {
	    if (room[current_room].getUp())
        {
	        if (current_room == 20)
            {
	            goNorth();
            }
            else if (current_room == 22)
            {
                goWest();
            }
            else if (current_room == 36)
            {
                goSouth();
            }
        }
        else if (!room[current_room].getUp())
        {
            feedback.assign("NOWHERE TO GO UP!");
        }
    }
    else if (((v == 3 && current_noun == noun[24]) || v == 9))
    {
        if (room[current_room].getDown())
        {
            if (current_room == 20)
            {
                goWest();
            }
            else if (current_room == 22)
            {
                goSouth();
            }
            else if (current_room == 36)
            {
                goNorth();
            }
        }
        else if (!room[current_room].getDown())
        {
            feedback.assign("NOWHERE TO GO DOWN!");
        }
    }
    else if (v == 3 && ((current_noun != noun[19]) || (current_noun != noun[20]) ||
    (current_noun != noun [21]) || (current_noun != noun[22])
    || (current_noun != noun[23]) || (current_noun != noun[24])))
    {
        feedback.assign("YOU CAN'T GO " + current_noun);
    }
	// Verbs GET and TAKE
	else if (v == 10 || v == 11)
	{
		if (room[current_room].getItems())
		{
			for (int i = 0; i < ITEM_COUNT; i++)
			{
				if (current_noun == noun[i] && items[i].isVisible()
					&& current_room == items[i].getItemRoom() && items[i].isGettable()
					&& !is_paralyzed)
				{
					items[i].setInInventory(true);
					items[i].setVisibe(false);
					feedback = "YOU GOT THE " + items[i].getName();
					item_string.clear();
					break;
				}
			}
		}
		else
		{
			feedback.assign("THERE ARE NO GETTABLE ITEMS IN THIS ROOM");
		}
	}
	//verb EXAMINE
	else if (v == 12)
    {
		if (current_room == 3 && current_noun == "RUBBISH")
		{
			feedback = "THAT STINKS!";
		}
		else if (current_room == 32 && current_noun == noun[30])
		{
			feedback = "AN OLD COAT. YOU WERE ABLE TO SPOT A KEY HANGING FROM ITS POCKET.";
			items[18].setVisibe(true);
		}
		else if (current_room == 43 && current_noun == noun[29])
		{
			feedback = "YOU CAN SEE A DRAWER";
		}
		else if (current_room == 43 && current_noun == "WALL")
		{
			feedback = "THERE IS SOMETHING BEYOND...";
		}
		else if (current_room == 38 && current_noun == "COFFIN")
		{
			feedback = "THAT'S CREEPY! BUT IT LOOKS LIKE IT CAN BE OPENED.";
		}
		else
		{
			feedback.assign("EXAMINE WHAT?");
		}
    }
    //verb OPEN
    else if (v == 13)
	{
    	if (current_noun == noun[28] && current_room == 43)
		{
    		items[17].setVisibe(true);
		}
		else if (current_room == 28 && current_noun == "DOOR")
		{
			if (door_locked)
			{
				feedback.assign("IT'S LOCKED.");
			}
			else
			{
				feedback.assign("IT'S ALREADY OPEN.");
			}
		}
		else if (current_room == 38 && current_noun == "COFFIN")
		{
			feedback.assign("ALL THAT IS LEFT INSIDE ARE ASHES AND A DIAMOND RING.");
			items[2].setVisibe(true);
		}
		else
		{
			feedback.assign("OPEN WHAT?");
		}
	}
	//verb READ
	else if (v == 14)
	{
		if (current_room == 42 && current_noun == "BOOKS")
		{
			feedback.assign("THEY SPEAK OF DEMONIC WORKS");
		}
		else if (current_noun == noun[3] && items[3].isInInventory())
		{
			feedback.assign("USE THESE WORDS WITH CARE 'XZANFAR'");
		}
		else if (current_noun == noun[5] && items[5].isInInventory())
		{
			feedback.assign("THE SCRIPT IS IN AN ALIEN TONGUE");
		}
		else
		{
			feedback.assign("READ WHAT?");
		}
	}
	//verb SAY
	else if (v == 15)
	{
		if (current_noun == "XZANFAR")
		{
			magic_barrier = false;
			room[45].setWest(true);
			feedback.assign("THE MAGICAL BARRIER DISAPPEARS");
		}
		else
		{
			feedback.assign("'" + current_noun + "' ECHOES THROUGH THE SILENCE.");
		}
	}
	//verb DIG
	else if (v == 16)
	{
		if (items[12].isInInventory())
		{
			if (current_room == 30)
			{
				input_copy.clear();
				room[31].setDesc("You dug the bars out and escaped to the east."
                     "\n You are in a mountainous area outside the house.");
				room[30].setName("Open Celler");
				room[30].setDesc("You dug the iron bars to the east and\n found an exit.");
				room[30].setEast(true);
				room[31].setWest(true);
				current_room++;
			}
			else
			{
				feedback.assign("YOU DUG A HOLE.");
			}
		}
		else
		{
			feedback.assign("DIGGING WITH YOUR HANDS IS NOT A GOOD IDEA.");
		}
	}
	//verb SWING
	else if (v == 17)
	{
		if (items[13].isInInventory())
		{
			if (current_room == 43)
			{
				feedback.assign("YOU BROKE THE THIN WALL! THERE IS A ROOM TO THE NORTH.");
				room[43].setDesc("The wall to the north is broken.\n There is a room on the other side\n which was previously hidden.");
				room[43].setNorth(true);
			}
			else
			{
				feedback.assign("WHOOSH!");
			}
		}
		else
		{
			feedback.assign("SWING WHAT?");
		}
	}
	//verb CLIMB
	else if (v == 18)
	{
		if (items[14].isInInventory())
		{
			if (current_room == 7 && current_noun == "TREE")
			{
				feedback.assign("CLIMBED UP. YOU CAN SEE FOREST TO THE WEST AND CLIFFS TO THE SOUTH.");
				on_tree = true;
			}
			else
			{
				feedback.assign("CLIMB " + current_noun + "?");
			}
		}
		else
		{
			feedback.assign("YOU NEED SOMETHING TO CLIMB WITH.");
		}
	}
	//verb LIGHT
	else if (v == 19)
	{
		if (current_noun == noun[17] && items[17].isInInventory())
		{
			if (items[8].isInInventory() && items[9].isInInventory())
			{
				candle_lit = true;
				feedback.assign("IT CASTS A FLICKERING LIGHT!");
			}
			else if (items[9].isInInventory())
			{
				feedback.assign("IT WILL BURN YOUR HAND! FIND SOMETHING TO HOLD IT WITH.");
			}
			else
			{
				feedback.assign("NOTHING TO LIGHT IT WITH.");
			}
		}
		else
		{
			feedback.assign("LIGHT WHAT?");
		}
	}
	//verb UNLIGHT
	else if (v == 20)
	{
		if (candle_lit)
		{
			candle_lit = false;
			feedback.assign("EXTINGUISHED");
		}
		else if (!candle_lit && feedback != "EXTINGUISHED")
		{
			feedback.assign("UNLIGHT WHAT?");
		}
	}
	//verb UNLOCK
	else if (v == 23)
	{
		if (current_room == 28 && door_locked)
		{
			door_locked = false;
			room[28].setSouth(true);
			feedback.assign("THE KEY TURNS!");
			room[28].setDesc("A passage with a wooden door which you unlocked.");
			room[28].setName("Hall with Open Door");
		}
		else if (current_room != 28)
		{
			feedback.assign("UNLOCK WHAT?");
		}
	}
	//verb LEAVE
	else if (v == 24)
	{
		if (current_noun == noun[15] && ((current_room == 62) || (current_room == 14)
		|| (current_room == 7)))
		{
			is_paralyzed = false;
		}
		for (auto &item : items) {
			if (current_noun == item.getName() && item.isInInventory())
			{
				feedback.assign("YOU LEFT " + item.getName());
				item.setInInventory(false);
				item.setVisibe(true);
				item.setItemRoom(current_room);
				item_string.clear();
				room[current_room].setHasItem(true);
				item.setItemRoom(current_room);
                break;
			}
		}
	}
	//verb SCORE
	else if (v == 25)
	{
		//display score
		std::string score_str = "SCORE: " + std::to_string(current_score);
		int num_items_in_inv = 0;
		for (auto &item : items)
		{
			if (item.isInInventory())
			{
				num_items_in_inv++;
			}
		}
		current_score = 2 * num_items_in_inv;
		if (current_verb == verb[25])
		{
			renderer->renderText(score_str,
								 820, 100, 1.0, ASGE::COLOURS::LIGHTGREEN);
		}
		else
		{
			score_str.clear();
		}
		if (current_score == 34 && current_room == 57)
		{
			feedback.assign("YOU WERE ABLE TO ESCAPE SUCCESSFULLY! CONGRATULATIONS!");
			item_string.assign("PRESS ENTER TO EXIT.");
			if (enter_pressed)
			{
				signalExit();
			}
		}
	}
}

void MyGame::update(const ASGE::GameTime &us) {
	current_desc = room[current_room].getDesc();
	//Look at the first word and match it to the second; if not found, display error;
	found_verb = false;
	for (int i = 0; i < VERB_COUNT; i++)
	{
		if (current_verb == verb[i])
		{
			found_verb = true;
			checkNoun(i);
			break;
		}
	}
	if (!found_verb)
	{
		feedback = "ENTER A VALID KEYWORD. 'HELP' FOR LIST OF KEYWORDS.";
	}
	// updates the exits that are displayed when entering a new room
	if (room_updated)
	{
		room_updated = false;
		exits.clear();
		item_string.clear();
		current_desc.clear();
		if (room[current_room].getNorth())
		{
			exits.append("|N| ");
		}
		if (room[current_room].getSouth())
		{
			exits.append("|S| ");
		}
		if (room[current_room].getWest())
		{
			exits.append("|W| ");
		}
		if (room[current_room].getEast())
		{
			exits.append("|E| ");
		}
        if (room[current_room].getUp())
        {
            exits.append("|U| ");
        }
        if (room[current_room].getDown())
        {
            exits.append("|D| ");
        }
	}
	//bats logic
	if (current_room == 13 && items[19].isVisible())
	{
		room[13].setWest(false);
		current_room = 13;
		is_paralyzed = true;
		feedback = "YOU HAVE BEEN ATTACKED BY BATS! YOU ARE PARALYZED AND CANNOT MOVE.";
		if (current_verb == verb[21] && items[16].isInInventory()
			&& (current_noun == noun[16] || current_noun == noun[26]))
		{
			is_paralyzed = false;
			feedback = "THE BATS UNLEASH A HORRIFYING SCREAM AND FALL ON THE GROUND.";
			items[19].setVisibe(false);
			room[13].setWest(true);
		}
	}
	//ghosts logic
	if (current_room == 52 && items[20].isVisible())
	{
		room[52].setWest(false);
		room[52].setNorth(false);
		current_room = 52;
		is_paralyzed = true;
		feedback = "YOU HAVE BEEN ATTACKED BY SPOOKY GHOSTS! YOU ARE PARALYZED AND CANNOT MOVE.";
		if (current_verb == verb[22] && items[10].isInInventory()
			&& items[11].isInInventory() && current_noun == noun[10])
		{
			is_paralyzed = false;
			feedback = "THE GHOSTS HAVE BEEN SUCKED UP!";
			items[20].setVisibe(false);
			room[52].setWest(true);
			room[52].setNorth(true);
		}
	}
	//boat login
	if (items[15].isInInventory() && !((current_room == 54) || (current_room == 55)
	|| (current_room == 47) || (current_room == 39) || (current_room == 31) ||
			(current_room == 23) || (current_room == 15)))
	{
		is_paralyzed = true;
		feedback = "THE BOAT IS TOO HEAVY TO CARRY!";
	}
	//Stuck in the marsh
	if (!items[15].isInInventory() && current_room == 54)
	{
		is_paralyzed = true;
		feedback = "YOU GOT STUCK IN THE MARSH!";
	}
	//candle logic
	if (candle_lit)
	{
		if (candle_life <= 1)
		{
			candle_lit = false;
		}
		else if (candle_life == 10)
		{
			feedback = "YOUR CANDLE IS WANING!";
		}
		else if (candle_life <= 2)
		{
			feedback = "YOUR CANDLE RUNS OUT!";
		}
	}
    //magical barrier
	if (current_room == 45 && items[1].isInInventory() && magic_barrier)
	{
		room[45].setWest(false);
		feedback.assign("A MAGICAL BARRIER BLOCKS YOUR WAY TO THE WEST.");
	}
	//divides player input (when there is a ' ' char) into two substrings
    found_space = input_copy.find_first_of(' ');
	if (found_space > 0 && enter_pressed)
	{
		current_verb = input_copy.substr(0, found_space);
		current_noun = input_copy.substr(found_space + 1);
	}
	//displays items in the room
	if (room[current_room].getItems())
	{
       	for (auto &item : items)
       	{
       		if (current_room == item.getItemRoom() && item.isVisible()
       		&& !item.isInInventory() && item.isGettable())
			{
       			item_string.assign("YOU CAN SEE " + item.getName());
       			break;
			}
		}
	}
	else
	{
		item_string.assign("");
	}
}

void MyGame::render(const ASGE::GameTime &us)
{
	renderer->renderText("The Haunted House Remastered",
		20, 150, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText("Your Location",
		20, 180, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText("Exits:",
		20, 240, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(item_string,
						 20, 410, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(room[current_room].getName(),
						 20, 210, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(exits,
						 100, 240, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(input,
						 20, 270, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(input_copy,
						 20, 300, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(current_verb,
						 20, 330, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(current_noun,
						 20, 360, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(feedback,
						 20, 390, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(current_desc,
						 400, 200, 1.0, ASGE::COLOURS::LIGHTSLATEGRAY);

//	for (int i = 0;i<7;i++)
//	{
//        if (specialItems[i].isVisible())
//        {
//            renderer->renderSprite(*specialItems[i].spriteComponent()->getSprite());
//        }
//    }
        if (specialItems[0].isVisible())
        {
            renderer->renderSprite(*specialItems[0].spriteComponent()->getSprite());
        }
}

