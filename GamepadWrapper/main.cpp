//
//  main.cpp
//  GamepadWrapper
//
//  Created by Carlo Alberto Barbano on 23/11/15.
//  Copyright © 2015 CHARSLAB. All rights reserved.
//

#include <iostream>
#include <vector>

#include "gamepad/Gamepad.h"
#include "SysEvents.h"
#include "Utils.h"

using namespace std;

void gamepadAttach(struct Gamepad_device *, void *);
void gamepadRemove(struct Gamepad_device *, void *);

void buttonDown(struct Gamepad_device *gamepad, unsigned int buttonId, double timestamp, void *context);
void buttonUp(struct Gamepad_device *gamepad, unsigned int buttonId, double timestamp, void *context);
void axisMove(struct Gamepad_device *gamepad, unsigned int axisId, float value, float lastValue, double timestamp, void *context);


bool running = true;



float sensitivity = 5;
float x_value = 0.0, y_value = 0.0;


std::vector<int> keycodes;
std::vector<bool> keystate;

void updateMouse();
void updateKeyboard();

int main(int argc, const char * argv[]) {
    
    keycodes.push_back(0x00);
    keycodes.push_back(0x01);
    keycodes.push_back(0x02);
    keycodes.push_back(0x0D);
    keycodes.push_back(0x38);
    keycodes.push_back(0x0F);
    
    for(int i = 0; i < keycodes.size(); i++) {
        keystate.push_back(false);
    }
        
    
    
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
        case 3:
            keystate[find(keycodes, 0x0F)] = true;//r
            break;
        
        case 4:
            mouseClick(MouseButtons::BUTTON_RIGHT);
            break;
            
        case 5:
            mouseClick(MouseButtons::BUTTON_LEFT);
            break;
            
        case 9:
            running = false;
            break;
        
        case 10:
            keystate[find(keycodes, 0x38)] = true; //SHIFT
            break;
            
        default: break;
    }
}

void buttonUp(struct Gamepad_device *gamepad, unsigned int buttonId, double timestamp, void *context) {
    cout << "Button up: " << buttonId << endl;
    
    switch(buttonId) {
        case 3:
            keystate[find(keycodes, 0x0F)] = false;//r
            break;
            
        case 4:
            mouseUp(MouseButtons::BUTTON_RIGHT);
            break;
            
        case 5:
            mouseUp(MouseButtons::BUTTON_LEFT);
            break;
          
        case 10:
            keystate[find(keycodes, 0x38)] = false; //SHIFT
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
                keystate[find(keycodes, 0x00)] = false; //a
                keystate[find(keycodes, 0x02)] = false; //d
            } else {
                if(value > 0)
                    keystate[find(keycodes, 0x02)] = true;
                else
                    keystate[find(keycodes, 0x00)] = true;
            }
            break;
            
        case 1:
            if(value == 0.0) {
                keystate[find(keycodes, 0x0D)] = false; //w
                keystate[find(keycodes, 0x01)] = false; //s

            } else {
                if(value > 0.0)
                    keystate[find(keycodes, 0x01)] = true;
                else
                    keystate[find(keycodes, 0x0D)] = true;
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
    
    //cout << "Cursor position: " << cursor.x << " " << cursor.y << endl;
    
    cursor.x += x_value*sensitivity;
    cursor.y += y_value*sensitivity;
   
    //cout << "New position:    " << cursor.x << " " << cursor.y << endl;
    
    setCursorPosition(cursor);
}

void updateKeyboard() {
      for(int i = 0;i < keycodes.size(); i++) {
        if(keystate[i])
            keyboardPress(keycodes[i]);
        else
            keyboardUp(keycodes[i]);
    }
}