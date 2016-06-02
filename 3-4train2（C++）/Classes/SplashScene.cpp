#include "SplashScene.h"

Scene* SplashScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}
bool SplashScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	background = Sprite::create("u3.jpg");
	background->setContentSize(Size(winSize.width * 2, winSize.height * 2));
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(Point(0, 0));
	this->addChild(background, 1);
	auto tollGateButton = Button::create();
	//之后会抽象出来，让多个Button重用
	{tollGateButton->loadTextureNormal("icon/play.png");
	tollGateButton->setPosition(Point(60, winSize.height * 7 / 8));
	tollGateButton->setScale(0.2);
	tollGateButton->setTag(1);}
	tollGateButton->addClickEventListener(CC_CALLBACK_1(SplashScene::selectTollGate, this));
	background->addChild(tollGateButton);
	//Director::getInstance()->pushScene(scene);
	return true;
}
void SplashScene::setTollGate(int tollGate){
	this->tollGate = tollGate;
}
void SplashScene::selectTollGate(Ref *pObjcet){
	setTollGate(1);
	auto scene = GameScene::createScene(tollGate);
	Director::getInstance()->replaceScene(scene);
}