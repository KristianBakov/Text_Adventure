//
// Created by Huxy on 03/10/2018.
//

#include "MyGame.h"
#include <Engine\Renderer.h>
#include "GameObject.h"
#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Platform.h>
#include <Engine/Sprite.h>
MyGame::~MyGame() {

}
bool MyGame::init(){
  if (!initAPI())
      return false;

  toggleFPS();
  renderer->setWindowTitle("This Game I Madez");

  return true;
}

void MyGame::update(const ASGE::GameTime &us)
{
   //do some stuff / what's going on here?
  return;
}

void MyGame::render(const ASGE::GameTime &us)
{
  renderer->renderText("Choose mode and press play to start",
                       200, 350, 1.5, ASGE::COLOURS::NAVAJOWHITE);
  return;
}
