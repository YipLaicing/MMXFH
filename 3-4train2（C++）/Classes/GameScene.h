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
		Sprite* Background;//����
		//��������
		string backgroundFilePath;//����ͼ
		int tollGate;//��ʾ��ǰ������һ��
		//��������þ���
		RoleSprite* selSprite;
		Sprite* touchSprite;
		//�𳵶���
		MoveBy* trainMove;
		//��ǩ 
		Label* score;
		Label* levelLabel;
		Label* lifeLabel;
		//��ť
		Button* pauseButton;
		
		Size winSize;
		float t = 0;
		//int GameTimes;
		//�𳵲���
		float trainWidth;
		float trainHorizon;
		float firstCargo;
		float cargoOffset;
		//һ�ε÷�
		int scoreOnce;
		//����ӷ� 
		int extraScore;
		//Ŀǰ����
		int scoreNumber;
		//ʣ������
		int life;
		//Ŀǰ�Ѷȵȼ�
		int difficultyLevel;
		//��С�Ѷȵȼ�
		int minDifficultyLevel;
		//����Ѷȵȼ�
		int maxDifficultyLevel;
		//��������
		int cargoCount;
		//�����ʼλ��
		//Point SpriteFirstPosition;
		//��ͣ�˵�
		Menu* pausemenu;
		//��Ҫ�����ȥ�����Լ�����
		//Sprite* carriage;
		//Sprite* goods;
		// implement the "static create()" method manually
		CREATE_FUNC(GameScene);
		//��������
		Sprite* train;//��
		Vector<RoleSprite *> carriageSprites;//���϶�����
		Vector<Sprite*>goodsSprites;//���ϱ�ʾ�������
		//��������
		virtual bool onTouchBegan(Touch* ptouch, Event* pevent);
		virtual void onTouchMoved(Touch* ptouch, Event* pevent);
		virtual void onTouchEnded(Touch* ptouch, Event* pevent);
		virtual void selectSpriteTouching(Point touchLocation);
		void selectSpriteForTouch(Point touchLocation);
		Point boundLayerPos(Point newPos);
		void panForTranslation(Point translation);
		//����ˢ��
		void update(float dt);
		//bool onContactBegin(const PhysicsContact& contact);
		//bool onContactPreSolve(const PhysicsContact& contact, PhysicsContactPreSolve &solve);
		//void onContactPostSolve(const PhysicsContact& contact, PhysicsContactPostSolve &solve);
		//void onContactSeperate(const PhysicsContact& contact);
		//void setPhysicsWorld(PhysicsWorld* world);
		// �����������麯��
		void createGoodsAndCarriage(int tollGate,int number);
		void createTrain(int number);
		//���س�����Ч
		void loadVoice();
		bool trainRunOutOfScreen();
		//��ͣ��ť�ص�����
		void pauseCallBack(Ref* pObjcet);
		//��ͣ�˵�
		void loadMenu(int pauseOrGameOver);
		//��Ϸ�����˵�
		void GameOverMenu();
		void retryCallBack(Ref* pObjcet);
		void resumeTheGame(Ref* pObject);
		void returnToGameSelect(Ref* pObject);
		void nextGame(Ref* pObject);
		void setTollParameter(int tollGate, string const&filepath);
};

