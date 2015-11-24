//
//  SysEvents.c
//  GamepadWrapper
//
//  Created by Carlo Alberto Barbano on 23/11/15.
//  Copyright © 2015 CHARSLAB. All rights reserved.
//

#include "SysEvents.h"

CGPoint getCursorPosition() {
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    
    return cursor;
}

void setCursorPosition(CGPoint cursor) {
    CGEventRef moveEvent = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, cursor, kCGMouseButtonLeft);
    CGEventPost(kCGSessionEventTap, moveEvent);
    CFRelease(moveEvent);
}

void mouseClick(enum MouseButtons btn) {
    switch(btn) {
        case BUTTON_LEFT: {
            CGEventRef mouseDownEv = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, getCursorPosition(), kCGMouseButtonLeft);
            CGEventPost(kCGHIDEventTap, mouseDownEv);
        }
            break;
            
        case BUTTON_RIGHT: {
            CGEventRef mouseDownEv = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, getCursorPosition(), kCGMouseButtonRight);
            CGEventPost(kCGHIDEventTap, mouseDownEv);
        }
            break;
            
        case BUTTON_MIDDLE: {
            CGEventRef mouseDownEv = CGEventCreateMouseEvent(NULL, kCGEventOtherMouseDown, getCursorPosition(), kCGMouseButtonCenter);
            CGEventPost(kCGHIDEventTap, mouseDownEv);
        }
            break;
            
        default: break;
    }
}

void mouseUp(enum MouseButtons btn) {
    switch(btn) {
        case BUTTON_LEFT: {
            CGEventRef mouseUpEv = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, getCursorPosition(), kCGMouseButtonLeft);
            CGEventPost(kCGHIDEventTap, mouseUpEv);
        }
            break;
            
        case BUTTON_RIGHT: {
            CGEventRef mouseUpEv = CGEventCreateMouseEvent(NULL, kCGEventRightMouseUp, getCursorPosition(), kCGMouseButtonRight);
            CGEventPost(kCGHIDEventTap, mouseUpEv);
        }
            break;
            
        case BUTTON_MIDDLE: {
            CGEventRef mouseUpEv = CGEventCreateMouseEvent(NULL, kCGEventOtherMouseUp, getCursorPosition(), kCGMouseButtonCenter);
            CGEventPost(kCGHIDEventTap, mouseUpEv);
        }
            break;
        default: break;
    }
}

void keyboardPress(CGKeyCode code) {
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    CGEventRef keyPress = CGEventCreateKeyboardEvent(source, code, true);
    //CGEventSetFlags(keyPress, kCGEventFlagMaskCommand);
    CGEventPost(kCGAnnotatedSessionEventTap, keyPress);
}

void keyboardUp(CGKeyCode code) {
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    CGEventRef keyUp = CGEventCreateKeyboardEvent(source, code, false);
    //CGEventSetFlags(keyPress, kCGEventFlagMaskCommand);
    CGEventPost(kCGAnnotatedSessionEventTap, keyUp);
}

