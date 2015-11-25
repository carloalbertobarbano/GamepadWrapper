//
//  SysEvents.h
//  GamepadWrapper
//
//  Created by Carlo Alberto Barbano on 23/11/15.
//  Copyright © 2015 CHARSLAB. All rights reserved.
//

#ifndef SysEvents_h
#define SysEvents_h

extern void Pause(int ms);
enum MouseButtons { BUTTON_LEFT, BUTTON_RIGHT, BUTTON_MIDDLE };

#ifdef __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#include <WinBase.h>
#endif

namespace GamepadWrapper {
    typedef struct {
        int x;
        int y;
    } Point;
}

extern GamepadWrapper::Point getCursorPosition();
extern void setCursorPosition(GamepadWrapper::Point cursor);
extern void mouseClick(enum MouseButtons btn = BUTTON_LEFT);
extern void mouseUp(enum MouseButtons btn = BUTTON_LEFT);

extern void keyboardPress(int code);
extern void keyboardUp(int code);

extern void Pause(int ms);



#endif /* SysEvents_h */
