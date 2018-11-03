//
// Created by Huxy on 03/10/2018.
//

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

  mouse_callback_id =inputs->addCallbackFnc(
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
  room[57].room(true,false,true,true,false,false,"Path by iron door","Spooky");
  room[57].room(true,false,true,true,false,false,"Path by railings","more spook");
}


void MyGame::keyHandler(const ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent *>(data.get());
}

void MyGame::clickHandler(const ASGE::SharedEventData data) {
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
void MyGame::update(const ASGE::GameTime &us)
{
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
  return;
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
