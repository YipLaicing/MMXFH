#pragma once
#include "cocos2d.h"
#include"GameScene.h"
#include"ui\UIButton.h"
using namespace cocos2d::ui;
USING_NS_CC;
class SplashScene :public cocos2d::Layer
{
private:
	Sprite* background;
	int tollGate;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SplashScene);
	void setTollGate(int tollGate);
	void selectTollGate(Ref *pObjcet);
};

