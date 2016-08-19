//
//  VungleWrapper.h
//  PowersOfTwo
//
//  Created by Freeman on 14-4-19.
//
//

#ifndef ACCESSIBILITY_WRAPPER_H_
#define ACCESSIBILITY_WRAPPER_H_

class AccesibilityWrapper{
    
public:
    static AccesibilityWrapper * getInstance();
    
    // init menu scene rect
	void initMenuSceneRect();
    
};

#endif /* defined(ACCESSIBILITY_WRAPPER_H_) */
