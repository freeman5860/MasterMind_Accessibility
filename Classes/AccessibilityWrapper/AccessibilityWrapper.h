//
//  VungleWrapper.h
//  PowersOfTwo
//
//  Created by Freeman on 14-4-19.
//
//

#ifndef ACCESSIBILITY_WRAPPER_H_
#define ACCESSIBILITY_WRAPPER_H_

class AccessibilityWrapper{
    
public:
    static AccessibilityWrapper * getInstance();
    
    // init menu scene rect
	void addMenuSceneRect(int i, const char * s, float l, float r, float t, float b);
    
};

#endif /* defined(ACCESSIBILITY_WRAPPER_H_) */
