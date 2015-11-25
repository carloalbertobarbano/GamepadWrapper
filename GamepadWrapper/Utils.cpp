//
//  Utils.cpp
//  GamepadWrapper
//
//  Created by Carlo Alberto Barbano on 25/11/15.
//  Copyright © 2015 CHARSLAB. All rights reserved.
//

#include "Utils.h"

int find(std::vector<int> v, int n) {
    for(int i = 0;i < v.size(); i++) {
        if(v[i] == n)
            return i;
    }
    
    return 0;
}