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

void MyGame::initializeRooms()
{
	room[57].room(true, false, true, true, false, false, "Path by iron door", "Spooky");
	room[57].room(true, false, true, true, false, false, "Path by railings", "more spook");
}


void MyGame::keyHandler(const ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent *>(data.get());
	inputText(key);
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
	if(key->key == ASGE::KEYS::KEY_ENTER &&key->action == ASGE::KEYS::KEY_PRESSED)
	{
		input.push_back('\n');
	}
}

void MyGame::update(const ASGE::GameTime &us) {
	/*if (the room has been updated)
	{
	if (the direction is set to true)
	{
	exits.push_back(add char for each true direction + ",");
	}
	else
	{
	exits.push_back(add "");
	}
	}*/
	renderer->renderText(input,
						 20, 270, 1.0, ASGE::COLOURS::LIGHTGREEN);
	//renderer->renderText(verb[1],
	//					 20, 300, 1.0, ASGE::COLOURS::LIGHTGREEN);
	found_verb = input.find_first_of(" ");
	if (found_verb > 0) {
		current_verb = input.substr(0, found_verb);
		renderer->renderText(current_verb,
							 20, 300, 1.0, ASGE::COLOURS::LIGHTGREEN);
	}
}

void MyGame::render(const ASGE::GameTime &us)
{
	renderer->renderText("The Haunted House Remastered",
		20, 150, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText("Your Location",
		20, 180, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText(room[current_room].getName(),
		20, 210, 1.0, ASGE::COLOURS::LIGHTGREEN);
	renderer->renderText("Exits:",
		20, 240, 1.0, ASGE::COLOURS::LIGHTGREEN);
	return;
}

