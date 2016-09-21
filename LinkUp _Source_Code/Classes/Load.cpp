#include "Load.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Runing.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio::timeline;

int b_last(-1);
int b_this(-1);
int road[24];
LU thepic;
LoadingBar* bar;


Scene* Load::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Load::create();

	
	//设置音量0.0-1.0
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.8);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
	//开始播放背景音乐，true表示循环
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM.mp3", true);
	//生成位置
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Load::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	if (trash != NULL) removeChild(trash);

	auto rootNode = CSLoader::createNode("LoadScene.csb");

	addChild(rootNode);
    trash = rootNode;

	int i, k1, k2;
	pos[0].x = pos[22].x = 240 + 60;
	pos[1].x = pos[23].x = 360 + 60;
	pos[0].y = pos[1].y = 1280 - 240 - 60;
	pos[22].y = pos[23].y = 1280 - 960 - 60;
	i = 2;
	for (k1 = 1280 - 360 - 60; k1 >= 1280 - 840 - 60; k1 -= 120) {
		for (k2 = 120 + 60; k2 <= 480 + 60; k2 += 120) {
			pos[i].x = k2;
			pos[i].y = k1;
			if (i++ == 21) break;
		}
		if (i == 22) break;
	}

	//通过按钮的名字获得按钮
	Button* b_start = dynamic_cast<Button*>(rootNode->getChildByName("start"));
	Button* b_exit = dynamic_cast<Button*>(rootNode->getChildByName("exit"));
	

	//添加监听
	b_start->addTouchEventListener(CC_CALLBACK_2(Load::goRunscene, this));
	b_exit->addTouchEventListener(CC_CALLBACK_2(Load::exitapp, this));

	return true;
}

//按钮响应函数
void Load::goRunscene(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		//按下按钮
	case Widget::TouchEventType::BEGAN:
	{
		SimpleAudioEngine::sharedEngine()->playEffect("kehuan.mp3");

		removeChild(trash);
		trash = NULL;

		auto rootNode = CSLoader::createNode("RunScene.csb");
		addChild(rootNode);
		trash = rootNode;

		int i = 0;
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b1"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b1_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b2"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b2_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b3"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b3_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b4"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b4_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b5"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b5_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b6"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b6_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b7"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b7_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b8"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b8_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b9"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b9_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b10"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b10_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b11"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b11_0"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b12"));
		item[i++] = dynamic_cast<Button*>(rootNode->getChildByName("b12_0"));

		Button* b_pause = dynamic_cast<Button*>(rootNode->getChildByName("b_pause"));
		Button* b_replay = dynamic_cast<Button*>(rootNode->getChildByName("b_replay"));
		Button* b_exit2 = dynamic_cast<Button*>(rootNode->getChildByName("b_exit2"));
        
		//添加监听
		b_pause->addTouchEventListener(CC_CALLBACK_2(Load::Pause,this));
		b_replay->addTouchEventListener(CC_CALLBACK_2(Load::Replay, this));
		b_exit2->addTouchEventListener(CC_CALLBACK_2(Load::ExitToMenu, this));
        
		bar = static_cast<LoadingBar*>(rootNode->getChildByTag(31));
		bar->setPercent(98.0);
        schedule(schedule_selector(Load::BarUpdate), 1.0f/60);

		b_last = b_this = -1;
		for (i = 0; i <= 23; i += 2) i_att[i] = i_att[i + 1] = (i + 2) / 2;
		NumOfNode = 24;
		random(road, 24);
		for (i = 0; i <= 23;i++) item[i]->setPosition(Vec2(pos[ road[i] ].x, pos[ road[i] ].y));

		thepic.init();
		thepic.UpdatePath(road);
		while (thepic.NumOfPath < 1) {
			Ram_road();
			for (i = 0; i <= 23; i++) {
				if(road[i]>=0) item[i]->setPosition(Vec2(pos[road[i]].x, pos[road[i]].y));
			}
			thepic.UpdatePath(road);
		}

		for (i = 0; i <= 23; i++) {
			item[i]->addTouchEventListener(CC_CALLBACK_2(Load::item_active, this, i));
		}
		
	}
	break;
	}
}
void Load::exitapp(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		//按下按钮
	case Widget::TouchEventType::BEGAN:
	{
		removeChild(trash);
		trash = NULL;
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
	break;
	}
}

void Load::CleanLine(float dt) {
	removeChildByTag(100);
}
void Load::BarUpdate(float t) {
	float per;
	per	= bar->getPercent();
	per -= 0.04;
	if (per <= 2.0) WinScene(false);
	else bar->setPercent(per);
}

void Load::item_active(Ref* pSender, Widget::TouchEventType type, int att) {
	switch (type)
	{
		//按下按钮
	case Widget::TouchEventType::BEGAN:
	{
		if (b_last == -1) {
			b_last = att;
		}else {
			b_this = att;
			item[b_last]->setBrightStyle(Widget::BrightStyle::NORMAL);
			if (i_att[b_this] == i_att[b_last]) {
				int bt(b_this), bl(b_last);
				thepic.UpdatePath(road);
				if ( thepic.path[ i_att[b_this] ].size()>0 ) {
					//---------------------
					//绘制路线，并消除方块
					SimpleAudioEngine::sharedEngine()->playEffect("xx.wav");
					int i;
					auto aline = DrawNode::create();
					aline->setTag(100);
					for (i = 0; i < thepic.path[i_att[b_this]].size() - 1; i++) {
						Vec2 a, b;
						a.x = thepic.path[i_att[b_this]][i].x, a.y = thepic.path[i_att[b_this]][i].y;
						b.x = thepic.path[i_att[b_this]][i+1].x, b.y = thepic.path[i_att[b_this]][i+1].y;
						aline->drawSegment(a, b, 12.0, Color4F::BLUE);
					}
					addChild(aline);
					//---------------------
					b_last = b_this = -1;
					road[bl] = road[bt] = -1;
					item[bl]->setPosition(Vec2(-100, -100));
					item[bt]->setPosition(Vec2(-100, -100));
					NumOfNode -= 2;
					if (NumOfNode <= 0) WinScene(true);
					else {
                        thepic.UpdatePath(road);
					    while (thepic.NumOfPath < 1) {
							Ram_road();
						    for (i = 0; i <= 23; i++) {
							    if (road[i] >= 0) item[i]->setPosition(Vec2(pos[road[i]].x, pos[road[i]].y));
						    }
						    thepic.UpdatePath(road);
					    }
					}
					
					scheduleOnce(schedule_selector(Load::CleanLine), 0.3f);
				}
			}
			if (b_this >= 0) {
				b_last = b_this;
				b_this = -1;
			}
		}
	}
	break;
	}
	if (b_last>=0)
	{
		item[b_last]->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	}
}

void Load::Pause(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
		//按下按钮
	case Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("kehuan.mp3");
		unschedule(schedule_selector(Load::BarUpdate));
		auto Pscene = CSLoader::createNode("PauseLayer.csb");
		Pscene->setTag(111);
		addChild(Pscene);

		Button* b_replay = dynamic_cast<Button*>(Pscene->getChildByTag(50));
		Button* b_continue = dynamic_cast<Button*>(Pscene->getChildByTag(51));

		//添加监听
		b_continue->addTouchEventListener(CC_CALLBACK_2(Load::Continue, this));
		b_replay->addTouchEventListener(CC_CALLBACK_2(Load::Replay, this));
	}
}

void Load::ExitToMenu(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
		//按下按钮
	case Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("kehuan.mp3");
		unscheduleAllSelectors();
		removeChild(trash);
		trash = NULL;
		Load::init();
	}
}

void Load::Replay(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
		//按下按钮
	case Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("kehuan.mp3");
		Ref* a;
		goRunscene(a,Widget::TouchEventType::BEGAN);
	}
}

void Load::Continue(Ref* pSender, Widget::TouchEventType type) {
	switch (type)
	{
		//按下按钮
	case Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("kehuan.mp3");
		removeChildByTag(111);
		schedule(schedule_selector(Load::BarUpdate), 1.0f / 60);
	}
}

void Load::WinScene(bool ifwin)
{
	unscheduleAllSelectors();
	removeChild(trash);
	auto win = CSLoader::createNode("WinScene.csb");
	if (ifwin) {
         win->removeChildByTag(60);
	     win->removeChildByTag(61);
	}
	addChild(win);
	trash = win;
	Button* b_replay = dynamic_cast<Button*>(win->getChildByTag(59));
	Button* b_exit2 = dynamic_cast<Button*>(win->getChildByTag(58));

	b_exit2->addTouchEventListener(CC_CALLBACK_2(Load::ExitToMenu, this));
	b_replay->addTouchEventListener(CC_CALLBACK_2(Load::Replay, this));
}

void Load::Ram_road(){
	int flag[24];
	for (int i=0; i < 24; i++) flag[i] = road[i];
	random(road);
	for (int i = 0; i < 24; i++) {
		if (flag[i] == -1) road[i] = flag[i];
	}
}
