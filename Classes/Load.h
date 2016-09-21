#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//使用UI引用的命名空间
using namespace cocos2d::ui;

struct ord {
	int x;
	int y;
};

class Load : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Load);

	Node* trash;
	Button* item[24];
	int i_att[24];
	ord pos[24];
	int NumOfNode;

	void delaytime(float t);
	void Ram_road();
	//按钮响应函数
	void goRunscene(Ref* pSender, Widget::TouchEventType type);
	void exitapp(Ref* pSender, Widget::TouchEventType type);
	void Pause(Ref* pSender, Widget::TouchEventType type);
	void ExitToMenu(Ref* pSender, Widget::TouchEventType type);
	void Replay(Ref* pSender, Widget::TouchEventType type);
	void Continue(Ref* pSender, Widget::TouchEventType type);
	void WinScene(bool ifwin);

	void item_active(Ref* pSender, Widget::TouchEventType type,int att);

	void CleanLine(float dt);
	void BarUpdate(float t);
};

#endif // __HELLOWORLD_SCENE_H__
