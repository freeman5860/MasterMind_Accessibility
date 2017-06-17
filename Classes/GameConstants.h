#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

#include "cocos2d.h"
USING_NS_CC;

class GameConstants
{
public:
    static const char * getPlayNodeDesc(int id){
		switch(id){
			case 0:
				return "play_node_0";
			case 1:
				return "play_node_1";
			case 2:
				return "play_node_2";
			case 3:
				return "play_node_3";
			case 4:
				return "play_node_4";
			case 5:
				return "play_node_5";
			case 6:
				return "play_node_6";
			case 7:
				return "play_node_7";
		}

		return "default_node";
	}

	static const char * getColor(int id){
		switch(id){
			case 0:
				return "play_node_1";
			case 1:
				return "play_node_2";
			case 2:
				return "play_node_3";
			case 3:
				return "play_node_4";
			case 4:
				return "play_node_5";
			case 5:
				return "play_node_6";
		}

		return "default_node";
	}
};

#endif /* __GAME_CONSTANTS_H__ */
