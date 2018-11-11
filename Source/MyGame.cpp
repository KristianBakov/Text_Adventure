#include <utility>

//
// Created by Huxy on 03/10/2018.
//

#include <iostream>
#include "MyGame.h"
#include "Rooms.h"
#include "Items.h"
#include <Engine\Renderer.h>
#include "GameObject.h"
#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Platform.h>
#include <Engine/Sprite.h>

MyGame::MyGame() = default;

MyGame::~MyGame() {
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
	current_room += 1;
	input_copy.clear();
	room_updated = true;
}
void MyGame::goWest()
{
	current_room -= 1;
	input_copy.clear();
	room_updated = true;
}
void MyGame::goNorth()
{
	current_room -= ROW;
	input_copy.clear();
	room_updated = true;
}
void MyGame::goSouth()
{
	current_room += ROW;
	input_copy.clear();
	room_updated = true;
}
void MyGame::initializeItems()
{
    items[1].item(46,noun[1],true,true,true); // painting
    items[2].item(38,noun[2],true,false,true); // ring
    items[3].item(35,noun[3],true,true,true); //book of spells
    items[4].item(50,noun[4],true,true,true); //goblet
    items[5].item(13,noun[5],true,true,true); //scroll
    items[6].item(18,noun[6],true,true,true); // coins
    items[7].item(28,noun[7],true,true,true); //statue
    items[8].item(42,noun[8],true,true,true); //candlestick
    items[9].item(10,noun[9],false,true,true); // matches
    items[10].item(25,noun[10],false,true,true); // vacuum
    items[11].item(26,noun[11],false,true,true); // batteries
    items[12].item(4,noun[12],false,true,true); //shovel
    items[13].item(2,noun[13],false,true,true); //axe
    items[14].item(7,noun[14],false,true,true); //rope
    items[15].item(47,noun[15],false,true,true); //boat
    items[16].item(60,noun[16],false,true,true); //aerosol
    items[17].item(43,noun[17],false,false,true); //candle
    items[18].item(32,noun[18],false,false,true); //key
    items[19].item(13,noun[26],false,true, false); //bats
    items[20].item(52,noun[27],false,true, false);//ghosts
    items[21].item(43,noun[28],false,false, false); //drawer
    items[22].item(43,noun[29],false,false, false); //desk
	items[23].item(32,noun[30],false,false, false); //coat

}
void MyGame::initializeRooms()
{
    room[0].room(false,true,true,false,false,false,"Dark corner","Spook", false);
    room[1].room(false,false,true,true,false,false,"Overgrown Garden","Spook", false);
    room[2].room(false,false,true,true,false,false,"By Woodpile","spook",true);
    room[3].room(false,true,true,true,false,false,"Rubbish Yard","sppok",false);
    room[4].room(false,false,true,true,false,false,"Weedpatch","", true);
    room[5].room(false,false,true,true,false,false,"Forest","",false);
    room[6].room(false,true,true,true,false,false,"Thick Forest","", false);
    room[7].room(false,true,false,true,false,false,"Blasted Tree","",true);
    room[8].room(true,true,false,false,false,false,"Corner of the House","",false);
    room[9].room(false,true,true,false,false,false,"Entrance to the Kitchen","",false);
    room[10].room(false,false,true,true,false,false,"Kitchen","",true);
    room[11].room(true,false,false,true,false,false,"Scullery door","",false);
    room[12].room(false,true,true,false,false,true,"Dusty room","",false);
    room[13].room(false,false,false,true,false,false,"Rear turret room","", true);
    room[14].room(true,false,true,false,false,false,"Clearing","",false);
    room[15].room(true,true,false,true,false,false,"Path","",false);
    room[16].room(true,true,false,false,false,false,"Side of House","",false);
    room[17].room(true,true,false,false,false,false,"Back of hallway","",false);
    room[18].room(false,true,true,false,false,false,"Dark Alcove","", true);
    room[19].room(false,false,true,true,false,false,"Small Dark Room","",false);
    room[20].room(true,false,false,true,true,true,"Spiral Staircase","",false);
    room[21].room(false,true,true,false,false,false,"Wide Passage","",false);
    room[22].room(false,true,false,true,true,true,"Slippery stairs","",false);
    room[23].room(true,true,false,false,false,false,"Clifftop","",false);
    room[24].room(true,false,false,false,false,false,"Crumbling Wall","",false);
    room[25].room(true,true,false,false,false,false,"Gloomy Passage","", true);
    room[26].room(true,true,true,false,false,false,"Pool of Light","",true);
    room[27].room(false,false,true,true,false,false,"Vaulted Hall","",false);
    room[28].room(false,true,true,true,false,true,"Hall with Locked Door","",true);
    room[29].room(true,true,false,true,false,false,"Trophy Room","",false);
    room[30].room(true,true,true,false,false,false,"Cellar","",false);
    room[31].room(true,true,false,false,false,false,"Cliff Path (North)","",false);
    room[32].room(false,true,false,false,false,false,"Cupboard","", true);
    room[33].room(true,true,true,false,false,false,"Front Hall","",false);
    room[34].room(true,true,false,true,false,false,"Sitting Room","",false);
    room[35].room(false,true,false,false,false,false,"Secret Room","",true);
    room[36].room(true,true,false,false,true,true,"Steep Marble Steps","",false);
    room[37].room(true,false,false,false,false,false,"Dining Room","",false);
    room[38].room(true,false,false,false,false,false,"Deep Cellar","",true);
    room[39].room(true,true,false,false,false,false,"Cliff Path (South)","",false);
    room[40].room(true,false,true,false,false,false,"Closet","",false);
    room[41].room(true,true,false,true,false,false,"Front Lobby","",false);
    room[42].room(true,false,true,false,false,false,"Library","",true);
    room[43].room(true,false,false,true,false,false,"Study","", true);
    room[44].room(true,true,true,false,false,false,"Cobwebby Room","",false);
    room[45].room(false,false,true,true,false,false,"Cold Chamber","",false);
    room[46].room(false,false,false,true,false,false,"Spooky Room","", true);
    room[47].room(true,true,false,false,false,false,"Cliff Path by Marsh","", true);
    room[48].room(false,true,true,false,false,false,"Verandah","",false);
	room[49].room(true, true, false, true, false, false, "Front Porch", "Spooky",false);
	room[50].room(false,false,true,false,false,false,"Front Tower","", true);
	room[51].room(false,false,true,true,false,false,"Slopping Corridor","",false);
	room[52].room(true,false,false,true,false,false,"Upper Gallery","",false);
	room[53].room(false,true,false,false,false,false,"Marsh by Wall","",false);
	room[54].room(false,true,true,true,false,false,"Marsh","",false);
	room[55].room(true,false,false,true,false,false,"Soggy Path","",false);
	room[56].room(true,false,true,false,false,false,"Twisted Railings","",false);
	room[57].room(true, false, true, true, false, false, "Path by iron door", "Spooky",false);
	room[58].room(false, false, true, true, false, false, "Path by railings", "more spook",false);
	room[59].room(false, false, true, true, false, false,"Beneath Tower","h",false);
	room[60].room(false, false, true, true, false, false,"Debris","h",true);
	room[61].room(true, false, true, true, false, false,"Fallen Brickwork","h",false);
	room[62].room(true, false, true, true, false, false,"Stone Arch","h",false);
	room[63].room(false, false, false, true, false, false,"Crumbling Clifftop","h",false);
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
	//Render available command
	else if (v == 1)
	{
		feedback.clear();
		for (int i=1;i<VERB_COUNT;i++)
		{
			feedback.append(verb[i] + ",");
			if (i % 6 == 0)
			{
				feedback.append("\n");
			}
		}
		feedback.pop_back();
	}
	//Moving around the grid;
	else if (((v == 3 && current_noun == noun[22]) || v == 7))
    {
            if (room[current_room].getEast())
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
	    if (room[current_room].getWest())
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
	    if (room[current_room].getSouth())
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
	    if (room[current_room].getNorth())
	    {
            goNorth();
        }
        else if (!room[current_room].getNorth())
        {
            feedback.assign("CAN'T GO FURTHER NORTH!");
        }
	}
	// Verbs GET and TAKE
	else if (v == 10 || v == 11)
	{
	    for (int i=0;i<ITEM_COUNT;i++) {
            if (current_noun == noun[i] && items[i].isVisible()
            && current_room == items[i].getItemRoom() && items[i].isGettable()
            && !is_paralyzed)
            {
                items[i].setInInventory(true);
                items[i].setVisibe(false);
                feedback = "YOU GOT THE " + items[i].getName();
                item_string.clear();
            }
        }
	}
//	else if (v == 12 && current_noun == items[ITEM_COUNT].getName())
//    {
//
//    }
}

void MyGame::update(const ASGE::GameTime &us) {
	renderer->renderText(room[current_room].getName(),
						 20, 210, 1.0, ASGE::COLOURS::LIGHTGREEN);

	// updates the exits that are displayed when entering a new room
	if (room_updated)
	{
		room_updated = false;
		exits.clear();
		if (room[current_room].getNorth()) {
			exits.append("|N| ");

		}
		if (room[current_room].getSouth()) {
			exits.append("|S| ");
		}
		if (room[current_room].getWest()) {
			exits.append("|W| ");
		}
		if (room[current_room].getEast()) {
			exits.append("|E| ");
		}
	}

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
	renderer->renderText(input,
						 20, 270, 1.0, ASGE::COLOURS::LIGHTGREEN);
	//renderer->renderText(verb[1],
	//					 20, 300, 1.0, ASGE::COLOURS::LIGHTGREEN);
	found_space = input_copy.find_first_of(' ');

	//divides player input (when there is a ' ' char) into two substrings
	if (found_space > 0 && enter_pressed) {
		current_verb = input_copy.substr(0, found_space);
		current_noun = input_copy.substr(found_space + 1);
	}
	renderer->renderText(exits,
						 100, 240, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(input_copy,
						 20, 300, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(current_verb,
						 20, 330, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(current_noun,
						 20, 360, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(feedback,
		             	20, 390, 1.0, ASGE::COLOURS::LIGHTGREEN);

        if (room[current_room].getItems())
		{
        	for (int i =0;i <ITEM_COUNT;i++)
			{
        		if (current_room == items[i].getItemRoom() && items[i].isVisible()
        		&& !items[i].isInInventory() && items[i].isGettable())
				{
        			item_string.assign(items[i].getName());
        			break;
				}
			}
		}
		else
		{
			item_string.assign("");
		}

    //Look at the first word and match it to the second; if not found, display error;
    found_verb = false;
	for (int i = 0; i < VERB_COUNT; i++)
	{
		if (current_verb == verb[i])
		{
			checkNoun(i);
			found_verb = true;
			break;
    	}
	}
    if (!found_verb)
    {
        feedback = "ENTER A VALID COMMAND. 'HELP' FOR LIST OF USABLE COMMANDS.";
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
	return;
}

