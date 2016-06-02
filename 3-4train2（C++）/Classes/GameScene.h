#pragma once
#include "cocos2d.h"
#include"SimpleAudioEngine.h"
#include"SpriteResource.h"
#include"SplashScene.h"
#include"RoleSprite.h"
#include"ui\UIButton.h"
using namespace cocos2d::ui;
using namespace CocosDenshion;
USING_NS_CC;
using namespace std;
class GameScene: public cocos2d::Layer
	{
	public:
		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene(int tollGate);
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();	    
		Sprite* Background;//背景
		//场景参数
		string backgroundFilePath;//背景图
		int tollGate;//表示当前处于哪一关
		//触摸检测用精灵
		RoleSprite* selSprite;
		Sprite* touchSprite;
		//火车动作
		MoveBy* trainMove;
		//标签 
		Label* score;
		Label* levelLabel;
		Label* lifeLabel;
		//按钮
		Button* pauseButton;
		
		Size winSize;
		float t = 0;
		//int GameTimes;
		//火车参数
		float trainWidth;
		float trainHorizon;
		float firstCargo;
		float cargoOffset;
		//一次得分
		int scoreOnce;
		//额外加分 
		int extraScore;
		//目前分数
		int scoreNumber;
		//剩余生命
		int life;
		//目前难度等级
		int difficultyLevel;
		//最小难度等级
		int minDifficultyLevel;
		//最大难度等级
		int maxDifficultyLevel;
		//货物数量
		int cargoCount;
		//精灵初始位置
		//Point SpriteFirstPosition;
		//暂停菜单
		Menu* pausemenu;
		//需要抽象出去车厢以及货物
		//Sprite* carriage;
		//Sprite* goods;
		// implement the "static create()" method manually
		CREATE_FUNC(GameScene);
		//场景精灵
		Sprite* train;//火车
		Vector<RoleSprite *> carriageSprites;//可拖动货物
		Vector<Sprite*>goodsSprites;//火车上标示所需货物
		//触摸控制
		virtual bool onTouchBegan(Touch* ptouch, Event* pevent);
		virtual void onTouchMoved(Touch* ptouch, Event* pevent);
		virtual void onTouchEnded(Touch* ptouch, Event* pevent);
		virtual void selectSpriteTouching(Point touchLocation);
		void selectSpriteForTouch(Point touchLocation);
		Point boundLayerPos(Point newPos);
		void panForTranslation(Point translation);
		//场景刷新
		void update(float dt);
		//bool onContactBegin(const PhysicsContact& contact);
		//bool onContactPreSolve(const PhysicsContact& contact, PhysicsContactPreSolve &solve);
		//void onContactPostSolve(const PhysicsContact& contact, PhysicsContactPostSolve &solve);
		//void onContactSeperate(const PhysicsContact& contact);
		//void setPhysicsWorld(PhysicsWorld* world);
		// 创建场景精灵函数
		void createGoodsAndCarriage(int tollGate,int number);
		void createTrain(int number);
		//加载场景音效
		void loadVoice();
		bool trainRunOutOfScreen();
		//暂停按钮回调函数
		void pauseCallBack(Ref* pObjcet);
		//暂停菜单
		void loadMenu(int pauseOrGameOver);
		//游戏结束菜单
		void GameOverMenu();
		void retryCallBack(Ref* pObjcet);
		void resumeTheGame(Ref* pObject);
		void returnToGameSelect(Ref* pObject);
		void nextGame(Ref* pObject);
		void setTollParameter(int tollGate, string const&filepath);
};

