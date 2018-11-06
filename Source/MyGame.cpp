#include <utility>

//
// Created by Huxy on 03/10/2018.
//

#include <iostream>
#include "MyGame.h"
#include "Rooms.h"
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

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &MyGame::keyHandler, this);

	mouse_callback_id = inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &MyGame::clickHandler, this);
	return true;
}

void MyGame::setupResolution()
{
	game_width = 1024;
	game_height = 768;
}
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
	current_room += ROW;
	input_copy.clear();
	room_updated = true;
}
void MyGame::goSouth()
{
	current_room -= ROW;
	input_copy.clear();
	room_updated = true;
}

void MyGame::initializeRooms()
{
    room[0].room(false,true,true,false,false,false,"Dark corner","Spook");
    room[1].room(false,false,true,true,false,false,"Overgrown Garden","Spook");
    room[2].room(false,false,true,true,false,false,"By Woodpile","spook");
    room[3].room(false,true,true,true,false,false,"Rubbish Yard","sppok");
    room[4].room(false,false,true,true,false,false,"Weedpatch","");
    room[5].room(false,false,true,true,false,false,"Forest","");
    room[6].room(false,true,true,true,false,false,"Thick Forest","");
    room[7].room(false,true,false,true,false,false,"Blasted Tree","");
    room[8].room(true,true,false,false,false,false,"Corner of the House","");
    room[9].room(false,true,true,false,false,false,"Entrance to the Kitchen","");
    room[10].room(false,false,true,true,false,false,"Kitchen","");
	room[49].room(true, false, true, true, false, false, "Path by iron door", "Spooky");
	room[57].room(true, false, true, true, false, false, "Path by iron door", "Spooky");
	room[58].room(true, false, true, true, false, false, "Path by railings", "more spook");
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
	if (v == 0)
	{
	feedback.assign("WHAT WILL YOU DO NEXT?");
	}
	if (((v == 3 && current_noun == noun[22]) || v == 7) && room[current_room].getEast())
    {
		goEast();
    }
	if (((v == 3 && current_noun == noun[21]) || v == 6) && room[current_room].getWest())
	{
		goWest();
	}
	if (((v == 3 && current_noun == noun[20]) || v == 5) && room[current_room].getSouth())
	{
		goSouth();
	}
	if (((v == 3 && current_noun == noun[19]) || v == 4) && room[current_room].getNorth())
	{
		goNorth();
	}
}

void MyGame::update(const ASGE::GameTime &us) {
	renderer->renderText(room[current_room].getName(),
						 20, 210, 1.0, ASGE::COLOURS::LIGHTGREEN);

	if (room_updated) {
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

	renderer->renderText(input,
						 20, 270, 1.0, ASGE::COLOURS::LIGHTGREEN);
	//renderer->renderText(verb[1],
	//					 20, 300, 1.0, ASGE::COLOURS::LIGHTGREEN);
	found_space = input_copy.find_first_of(' ');

	if (found_space > 0 && enter_pressed) {
		current_verb = input_copy.substr(0, found_space);
		current_noun = input_copy.substr(found_space + 1);
	}
	renderer->renderText(input_copy,
						 20, 300, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(current_verb,
						 20, 330, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(current_noun,
						 20, 360, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(feedback,
						 20, 390, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(exits,
                         100, 240, 1.0, ASGE::COLOURS::LIGHTGREEN);


	for (int i = 0; i < 26; i++) {
		if (current_verb == verb[i]) {
			checkNoun(i);
		}
		else {
			//call a function 'error msg'
			//feedback.clear();
		}
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
	return;
}

