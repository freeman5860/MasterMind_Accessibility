#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

#include "cocos2d.h"
USING_NS_CC;

#define DEFAULT_NODE "未知标签"

#define MENU_NODE_1 "开始游戏"
#define MENU_NODE_2 "怎么玩"

#define PLAY_NODE_0 "关闭按键"
#define PLAY_NODE_1 "红色地鼠"
#define PLAY_NODE_2 "绿色地鼠"
#define PLAY_NODE_3 "蓝色地鼠"
#define PLAY_NODE_4 "黄色地鼠"
#define PLAY_NODE_5 "白色地鼠"
#define PLAY_NODE_6 "黑色地鼠"
#define PLAY_NODE_7 "再玩一次"

#define COLOR_1 "红"
#define COLOR_2 "绿"
#define COLOR_3 "蓝"
#define COLOR_4 "黄"
#define COLOR_5 "白"
#define COLOR_6 "黑"

#define ROW_RESULT "第%d轮，%s%s%s%s，%d个猜中位置和颜色, %d个猜中颜色但位置不对"
#define GAME_OVER "%s，正确答案是%s%s%s%s, 花费时间%s"

class GameConstants
{
public:
    static const char * getMenuNodeDesc(int id){
		switch(id){
			case 0:
				return MENU_NODE_1;
			case 1:
				return MENU_NODE_2;
		}

		return DEFAULT_NODE;
	}
    static const char * getPlayNodeDesc(int id){
		switch(id){
			case 0:
				return PLAY_NODE_0;
			case 1:
				return PLAY_NODE_1;
			case 2:
				return PLAY_NODE_2;
			case 3:
				return PLAY_NODE_3;
			case 4:
				return PLAY_NODE_4;
			case 5:
				return PLAY_NODE_5;
			case 6:
				return PLAY_NODE_6;
			case 7:
				return PLAY_NODE_7;
		}

		return DEFAULT_NODE;
	}

	static const char * getColor(int id){
		switch(id){
			case 0:
				return COLOR_1;
			case 1:
				return COLOR_2;
			case 2:
				return COLOR_3;
			case 3:
				return COLOR_4;
			case 4:
				return COLOR_5;
			case 5:
				return COLOR_6;
		}

		return DEFAULT_NODE;
	}
};

#endif /* __GAME_CONSTANTS_H__ */
