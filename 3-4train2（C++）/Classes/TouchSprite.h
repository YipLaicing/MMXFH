#pragma once
#include"cocos2d.h"
USING_NS_CC;
typedef enum{
	kPaddleStateGrabbed,
	kPaddleStateUngrabbed
}PaddleState;
class TouchSprite:public Sprite
{
private:
	PaddleState _state;
	Point m_oldPoint;
	Point FirstPosition;
	int bitmask;
public:
	TouchSprite();
	virtual~TouchSprite();
	static TouchSprite* create(const std::string &modelPath);
	Rect getRect();
	virtual void onEnter() override;
	virtual void onExit() override;
	//virtual void setPosition(const Vec2&position) override;
	bool containsTouchLocation(Touch* touch);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void setBitmask(int bitmask);
	int getBitmask();
};

