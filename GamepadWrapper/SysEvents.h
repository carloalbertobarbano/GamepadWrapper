//
//  SysEvents.h
//  GamepadWrapper
//
//  Created by Carlo Alberto Barbano on 23/11/15.
//  Copyright © 2015 CHARSLAB. All rights reserved.
//

#ifndef SysEvents_h
#define SysEvents_h

#include <ApplicationServices/ApplicationServices.h>

enum MouseButtons { BUTTON_LEFT, BUTTON_RIGHT, BUTTON_MIDDLE };
extern CGPoint getCursorPosition();
extern void setCursorPosition(CGPoint cursor);
extern void mouseClick(enum MouseButtons btn = BUTTON_LEFT);
extern void mouseUp(enum MouseButtons btn = BUTTON_LEFT);

extern void keyboardPress(CGKeyCode code);
extern void keyboardUp(CGKeyCode code);

#endif /* SysEvents_h */
