//
// Created by Huxy on 03/10/2018.
//

#ifndef HELLOASGE_MYGAME_H
#define HELLOASGE_MYGAME_H

#include <string>
#include <Engine/OGLGame.h>

#include "GameObject.h"
#include "Rect.h"

class MyGame : public ASGE::OGLGame
{
public:
    MyGame();
    virtual ~MyGame();
    bool init() override;
    void update(const ASGE::GameTime& us) override;
    void render(const ASGE::GameTime& us) override;
private:
    void keyHandler(const ASGE::SharedEventData data);
    void clickHandler(const ASGE::SharedEventData data);
    void setupResolution();

    int key_callback_id = -1;	        /**< Key Input Callback ID. */
    int  mouse_callback_id = -1;        /**< Mouse Input Callback ID. */

    rect mouse_cursor;
};


#endif //HELLOASGE_MYGAME_H
