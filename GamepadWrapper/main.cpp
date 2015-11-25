//
//  main.cpp
//  GamepadWrapper
//
//  Created by Carlo Alberto Barbano on 23/11/15.
//  Copyright © 2015 CHARSLAB. All rights reserved.
//

#include <iostream>

#include "gamepad/Gamepad.h"
#include "SysEvents.h"


using namespace std;

void gamepadAttach(struct Gamepad_device *, void *);
void gamepadRemove(struct Gamepad_device *, void *);

void buttonDown(struct Gamepad_device *gamepad, unsigned int buttonId, double timestamp, void *context);
void buttonUp(struct Gamepad_device *gamepad, unsigned int buttonId, double timestamp, void *context);
void axisMove(struct Gamepad_device *gamepad, unsigned int axisId, float value, float lastValue, double timestamp, void *context);


bool running = true;



float sensitivity = 5;
float x_value = 0.0, y_value = 0.0;

bool w_pressed = false, a_pressed = false, s_pressed = false, d_pressed = false;
void updateMouse();
void updateKeyboard();

int main(int argc, const char * argv[]) {
    Gamepad_deviceAttachFunc(gamepadAttach, NULL);
    Gamepad_deviceRemoveFunc(gamepadRemove, NULL);
    
    cout << "Waiting for a device.." << endl;
    Gamepad_init();
    Gamepad_detectDevices();
    
    Gamepad_buttonDownFunc(buttonDown, NULL);
    Gamepad_buttonUpFunc(buttonUp, NULL);
    Gamepad_axisMoveFunc(axisMove, NULL);
    
    
    /* TEST KEY HERE: */
    
    while(running){
        Gamepad_processEvents();
        
        updateMouse();
        updateKeyboard();
        
		Pause(5);
    }

   
    
    cout << "Exitting.." << endl;
    
    Gamepad_shutdown();
    return 0;
}


void gamepadAttach(struct Gamepad_device *gamepad, void *context) {
    cout << "New device attached:" << endl;
    cout << "\tID: " << gamepad->deviceID << endl;
    cout << "\tDescription: " << gamepad->description << endl;
    cout << "\tNum. Axes: " << gamepad->numAxes << endl;
    cout << "\tNum. Buttons: " << gamepad->numButtons << endl;
}

void gamepadRemove(struct Gamepad_device *gamepad, void *context) {
    cout << "Device removed.." << endl;
    //running = false;
}



void buttonDown(struct Gamepad_device *gamepad, unsigned int buttonId, double timestamp, void *context) {
    cout << "Pressed button: " << buttonId << endl;
    
    switch(buttonId) {
        case 4:
            mouseClick(MouseButtons::BUTTON_RIGHT);
            break;
            
        case 5:
            mouseClick(MouseButtons::BUTTON_LEFT);
            break;
            
        case 9:
            running = false;
            break;
            
        default: break;
    }
}

void buttonUp(struct Gamepad_device *gamepad, unsigned int buttonId, double timestamp, void *context) {
    cout << "Button up: " << buttonId << endl;
    
    switch(buttonId) {
        case 4:
            mouseUp(MouseButtons::BUTTON_RIGHT);
            break;
            
        case 5:
            mouseUp(MouseButtons::BUTTON_LEFT);
            break;
            
        default: break;
    }
}



void axisMove(struct Gamepad_device *gamepad, unsigned int axisId, float value, float lastValue, double timestamp, void *context) {
    cout << "Axis " << axisId << " moved: " << value << endl;
    
    static float deadZone = 0.1;
    if(value < deadZone && value > -deadZone)
        value = 0.0;
    
    switch(axisId) {
        case 0:
            if(value == 0.0) {
                a_pressed = false;
                d_pressed = false;
                keyboardUp(0x00);
                keyboardUp(0x02);
            } else {
                if(value > 0)
                    d_pressed = true;
                    //keyboardPress(0x02);
                else
                    a_pressed = true;
                    //keyboardPress(0x00);
            }
            break;
            
        case 1:
            if(value == 0.0) {
                w_pressed = false;
                s_pressed = false;
                keyboardUp(0x0D);
                keyboardUp(0x01);
            } else {
                if(value > 0.0)
                    s_pressed = true;
                    //keyboardPress(0x01);
                else
                    w_pressed = true;
                    //keyboardPress(0x0D);
            }
            break;
            
        case 2:
            x_value = value;
            break;
            
        case 3:
            y_value = value;
            break;
            
        default: break;
    }
}

void updateMouse() {
    GamepadWrapper::Point cursor = getCursorPosition();
    
    cursor.x += x_value*sensitivity;
    cursor.y += y_value*sensitivity;
    
    
    setCursorPosition(cursor);
}

void updateKeyboard() {
    if(a_pressed)
        keyboardPress(0x00);
    else
        keyboardUp(0x00);
    
    if(d_pressed)
        keyboardPress(0x02);
    else
        keyboardUp(0x02);
    
    if(w_pressed)
        keyboardPress(0x0D);
    else
        keyboardUp(0x0D);
    
    if(s_pressed)
        keyboardPress(0x01);
    else
        keyboardUp(0x01);
}