//
//  SysEvents.c
//  GamepadWrapper
//
//  Created by Carlo Alberto Barbano on 23/11/15.
//  Copyright © 2015 CHARSLAB. All rights reserved.
//

#include "SysEvents.h"


void Pause(int ms) {
#ifdef __APPLE__
	usleep(ms * 1000);
#endif
	
#ifdef _WIN32
	Sleep(ms);
#endif
}


#ifdef __APPLE__
GamepadWrapper::Point getCursorPosition() {
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    
    GamepadWrapper::Point pt;
	pt.x = cursor.x;
	pt.y = cursor.y;

    return pt;
}

void setCursorPosition(GamepadWrapper::Point cursor) {
	CGPoint cgpt;
	cgpt.x = cursor.x;
	cgpt.y = cursor.y;

    CGEventRef moveEvent = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, cgpt, kCGMouseButtonLeft);
    CGEventPost(kCGSessionEventTap, moveEvent);
    CFRelease(moveEvent);
}

void mouseClick(enum MouseButtons btn) {
    switch(btn) {
        case BUTTON_LEFT: {
            CGPoint cursor = { static_cast<CGFloat>(getCursorPosition().x), static_cast<CGFloat>(getCursorPosition().y) };
            CGEventRef mouseDownEv = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, cursor, kCGMouseButtonLeft);
            CGEventPost(kCGHIDEventTap, mouseDownEv);
        }
            break;
            
        case BUTTON_RIGHT: {
            CGPoint cursor = { static_cast<CGFloat>(getCursorPosition().x), static_cast<CGFloat>(getCursorPosition().y) };
            CGEventRef mouseDownEv = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, cursor, kCGMouseButtonRight);
            CGEventPost(kCGHIDEventTap, mouseDownEv);
        }
            break;
            
        case BUTTON_MIDDLE: {
            CGPoint cursor = { static_cast<CGFloat>(getCursorPosition().x), static_cast<CGFloat>(getCursorPosition().y) };
            CGEventRef mouseDownEv = CGEventCreateMouseEvent(NULL, kCGEventOtherMouseDown, cursor, kCGMouseButtonCenter);
            CGEventPost(kCGHIDEventTap, mouseDownEv);
        }
            break;
            
        default: break;
    }
}

void mouseUp(enum MouseButtons btn) {
    switch(btn) {
        case BUTTON_LEFT: {
            CGPoint cursor = { static_cast<CGFloat>(getCursorPosition().x), static_cast<CGFloat>(getCursorPosition().y) };
            CGEventRef mouseUpEv = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, cursor, kCGMouseButtonLeft);
            CGEventPost(kCGHIDEventTap, mouseUpEv);
        }
            break;
            
        case BUTTON_RIGHT: {
            CGPoint cursor = { static_cast<CGFloat>(getCursorPosition().x), static_cast<CGFloat>(getCursorPosition().y) };
            CGEventRef mouseUpEv = CGEventCreateMouseEvent(NULL, kCGEventRightMouseUp, cursor, kCGMouseButtonRight);
            CGEventPost(kCGHIDEventTap, mouseUpEv);
        }
            break;
            
        case BUTTON_MIDDLE: {
            CGPoint cursor = { static_cast<CGFloat>(getCursorPosition().x), static_cast<CGFloat>(getCursorPosition().y) };
            CGEventRef mouseUpEv = CGEventCreateMouseEvent(NULL, kCGEventOtherMouseUp, cursor, kCGMouseButtonCenter);
            CGEventPost(kCGHIDEventTap, mouseUpEv);
        }
            break;
        default: break;
    }
}

void keyboardPress(int code) {
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    CGEventRef keyPress = CGEventCreateKeyboardEvent(source, code, true);
    //CGEventSetFlags(keyPress, kCGEventFlagMaskCommand);
    CGEventPost(kCGAnnotatedSessionEventTap, keyPress);
}

void keyboardUp(int code) {
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    CGEventRef keyUp = CGEventCreateKeyboardEvent(source, code, false);
    //CGEventSetFlags(keyPress, kCGEventFlagMaskCommand);
    CGEventPost(kCGAnnotatedSessionEventTap, keyUp);
}

#endif

#ifdef _WIN32 

Point getCursorPosition() {
	POINT p;
	GetCursorPos(&p);

    GamepadWrapper::Point cursor = { p.x, p.y };
	return cursor;
}

void setCursorPosition(GamepadWrapper::Point cursor) {
	SetCursorPos(cursor.x, cursor.y);
}

void mouseClick(enum MouseButtons btn) {
	GamepadWrapper::Point cursor = getCursorPosition();
	mouse_event(MOUSEEVENTF_LEFTDOWN, cursor.x, cursor.y, 0, 0);
}

void mouseUp(enum MouseButtons btn) {
	GamepadWrapper::Point cursor = getCursorPosition();
	mouse_event(MOUSEEVENTF_LEFTUP, cursor.x, cursor.y, 0, 0);
}

void keyboardPress(int code) {

}

void keyboardUp(int code) {

}



#endif