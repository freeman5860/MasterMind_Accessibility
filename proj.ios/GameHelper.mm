//
//  GameHelper.cpp
//  MasterMind
//
//  Created by Freeman on 14-1-9.
//
//

#include "GameHelper.h"

void GameHelper::moreGame(){
    [[UIApplication sharedApplication]openURL:[NSURL URLWithString:@"http://www.freemanapp.com"]];
}

