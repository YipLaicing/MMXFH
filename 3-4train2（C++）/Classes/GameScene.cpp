#include "GameScene.h"
Scene* GameScene::createScene(int tollGate)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	/*auto scene = Scene::createWithPhysics();
	//������������
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));*/
	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	//layer->setPhysicsWorld(scene->getPhysicsWorld());
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	loadVoice();
	//��Ϸ��������
	life = 3;
	scoreNumber = 0;
	scoreOnce = 200;
	extraScore = 500;
	minDifficultyLevel = 1;
	maxDifficultyLevel = 20;
	cargoCount = 3;
	backgroundFilePath = "3-4scene.png";
	//��ȡ��Ļ��С
	auto director = Director::getInstance();
    winSize = director->getWinSize();

	//ָ����������߽�
	/*auto body = PhysicsBody::createEdgeBox(Size(winSize.width*4, winSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 1.0f);
	auto edgeNode = Node::create();
	//edgeNode->setAnchorPoint(Point(0, 0));
	edgeNode->setPosition(Vec2(winSize.width/2, winSize.height/2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	//��ʼ����ײ������
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(GameScene::onContactPreSolve,this);
	//contactListener->onContactPostSolve = CC_CALLBACK_2(GameScene::onContactPostSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	*/
	//����ͼ
	Background = Sprite::create(backgroundFilePath);
	//Background->setContentSize(Size(winSize.width, winSize.height));
	//Background->setScaleX(winSize.width/Background->getContentSize().width);
	//Background->setScaleY(winSize.height/Background->getContentSize().height);
	Background->setAnchorPoint(Point(0, 0));
	Background->setPosition(Point(0, 0));
	this->addChild(Background, 1);
	//������ǩ
    score = Label::createWithSystemFont("score:0", "futura-48.fnt", 20);
	score->setPosition(Point(0.65f*winSize.width, 0.05f*winSize.height));
	score->setColor(Color3B::WHITE);
	Background->addChild(score);
	//�Ѷȱ�ǩ
	levelLabel = Label::createWithSystemFont("level:1", "futura-48.fnt", 20);
	levelLabel->setPosition(Point(0.25f*winSize.width, 0.05f*winSize.height));
	levelLabel->setColor(Color3B::WHITE);
	Background->addChild(levelLabel);
	//ʣ��������ǩ
	lifeLabel = Label::createWithSystemFont("life:XXX", "futura-48.fnt", 20);
	lifeLabel->setPosition(Point(0.85f*winSize.width, 0.05f*winSize.height));
	lifeLabel->setColor(Color3B::WHITE);
	Background->addChild(lifeLabel);
	//С��
	createTrain(5);
	
	//���س���
	createGoodsAndCarriage(1,cargoCount);
	//��������
	/*auto Rail = Sprite::create("3-4/rail.png");
	Rail->setPosition(Point(winSize.width / 2.0f, winSize.height / 5.0f));
	Rail->setScale((winSize.height / Rail->getContentSize().height)*0.13f);
	Background->addChild(Rail);*/
	//������Ч
	loadVoice();
	//��ͣ��ť
    pauseButton = Button::create(); 
	pauseButton->loadTextureNormal("pause.png");
	pauseButton->addClickEventListener(CC_CALLBACK_1(GameScene::pauseCallBack, this));
	pauseButton->setPosition(Point(60, winSize.height*7/8));
	pauseButton->setScale(0.5);
	Background->addChild(pauseButton);
	
	//������������
    auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->removeEventListenersForTarget(Background);
	this->scheduleUpdate();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("effects/BGM_1.wav",true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
	return true;
}

void GameScene::update(float dt){
	//ˢ�½���60Hz
	trainRunOutOfScreen();
}
//��ײ��⡪����ײ����ʱ���д���
/*bool GameScene::onContactBegin(const PhysicsContact& contact){
	
	//�����Ƴ��󣬳�����ʾЧ��������ͼ
	//ֱ��ͨ��ͼƬ����
	//CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("bg2.png");
    //spriteA->setTexture(texture);
	//ͨ������֡�滻
    //ʹ��setDisplayFrame(CCSpriteFrame*)���������þ���֡��������ͼƬ��
	//����plist�ļ������� 
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bg_0.plist");
	//ʹ�þ���֡���������� 
	//CCSprite* bg = CCSprite::createWithSpriteFrameName("bg1.png");
	//��������ͼƬ 
	//CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg2.png");
	//bg->setDisplayFrame(frame);
	// 




	//Background->removeChildByTag(spriteB->getTag());
	//��������ֵ�������в�������
	//carriageSprites.eraseObject((TouchSprite*)spriteB);
	//carriageSprites.erase(spriteB->getTag());
	//�ɹ�ƥ�䣬������ҷ���
	return true;
}
bool GameScene::onContactPreSolve(const PhysicsContact& contact, PhysicsContactPreSolve &solve){ 
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if (spriteA->getTag() > 0){
		carriageSprites.eraseObject((TouchSprite*)spriteA);
		//Background->removeChildByTag(spriteA->getTag());
		spriteA->removeFromParentAndCleanup(true);
		scoreNumber += 100;
		score->setString(StringUtils::format("score:%d", scoreNumber));
	}
	else{
		carriageSprites.eraseObject((TouchSprite*)spriteB);
		//Background->removeChildByTag(spriteB->getTag());
		spriteB->removeFromParentAndCleanup(true);
		scoreNumber += 100;
		score->setString(StringUtils::format("score:%d", scoreNumber));
	}
	return true; }
void GameScene::onContactPostSolve(const PhysicsContact& contact, PhysicsContactPostSolve &solve){ 
	
}
void GameScene::onContactSeperate(const PhysicsContact& contact){
	
}


void GameScene::setPhysicsWorld(PhysicsWorld* world){ this->m_world = world; }
*/
//�������Ｐ���Ӧ����
void GameScene::createGoodsAndCarriage(int tollGate,int number){
	SpriteResource m_SpriteResource =SpriteResource();
	vector<string> image = m_SpriteResource.getResource(tollGate,number);
	//���������
	vector<int>randNum;
	randNum.clear();
	for (int i = 0; i < number; i++){ randNum.push_back(i); }
	srand(NULL);
	for (int i = 0; i < number; i++){ int j = rand() % number; swap(randNum[i], randNum[j]); }
	//δд�ã����޸�
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
	//���ػ���
	carriageSprites.clear();
	goodsSprites.clear();
	for (int i = 0; i < image.size(); i++){
		//std::string image = SpriteImage[i];
		//����
		RoleSprite* carriage = RoleSprite::create(image[i]);
		/*PhysicsBody* body = PhysicsBody::createBox(carriage->getContentSize()*0.8f);
		//body->setContactTestBitmask(1 << i);
		//body->setCategoryBitmask(1 << i);
		//body->setCollisionBitmask(1 << i);
		body->setContactTestBitmask(0);
		body->setCategoryBitmask(0);
		body->setCollisionBitmask(0);
		carriage->setBitmask(1 << i);
		//body->setDynamic(false);
		carriage->setPhysicsBody(body);*/
		carriage->setName(image[i]);
		carriage->setScale(0.7f);
		carriage->setTag(i+1);
		float offsetFraction = ((float)(i + 1)) /(image.size()+1);
		carriage->setPosition(winSize.width*offsetFraction, winSize.height * 4 / 5);
		carriage->setSpritePosition(carriage->getPosition());
		Background->addChild(carriage, 21);
		//�ѻ��������ӽ���̬������й���
		carriageSprites.pushBack(carriage);		
		//����
		Sprite* good = Sprite::create(image[i]);
		/*PhysicsBody* m_body = PhysicsBody::createBox(good->getContentSize()*0.8);
		m_body->setCategoryBitmask(1 << i);
		m_body->setContactTestBitmask(1 << i);
		m_body->setCollisionBitmask(1 << i);
		//m_body->setDynamic(false);
		//m_body->setCategoryBitmask(1 << i);
		good->setPhysicsBody(m_body);*/
		good->setName(image[i]);
		good->setScale(winSize.height/good->getContentSize().height*0.04f);
		//float offsetPosition = (float)(randNum[i]+1) / (image.size()+1);
		good->setPosition(Point(-trainWidth/2.0f+firstCargo-(randNum[i]+1.3)*cargoOffset,trainHorizon));
		good->setColor(Color3B::GRAY);
		MoveBy* move = MoveBy::create(20 - t, Point(winSize.width+trainWidth+cargoOffset, 0));
		good->runAction(move);
		Background->addChild(good, 20);
		goodsSprites.pushBack(good);
	}
}
//��Ϸʤ���ж�
bool GameScene::trainRunOutOfScreen(){
	//ˢ���µ�һ������&&�ж���Ҹ����λ����Ƿ�ɹ�װж

	//֮���ģ�������update���棬ֱ���ö����ص�
	if (train->getPositionX() > (winSize.width+trainWidth/2-cargoOffset)){ 
		//�жϻ����Ƿ����װж�����񣬿۳�����
		if (carriageSprites.empty()){
			//�ɹ�װж,�����»�
			scoreNumber += extraScore;
			score->setString(StringUtils::format("score:%d", scoreNumber));
		}
		else{
			//װжʧ�ܣ��۳�����
			life--;
			SimpleAudioEngine::getInstance()->playEffect("effects/ao.wav");
			switch (life)
			{
			case 0:
				lifeLabel->setString(StringUtils::format("life:%s", ""));
				SimpleAudioEngine::getInstance()->playEffect("effects/lose.mp3");
				GameOverMenu();
				//������Ϸ����scene
				break;
			case 1:
				lifeLabel->setString(StringUtils::format("life:%s", "X"));
				break;
			case 2:
				lifeLabel->setString(StringUtils::format("life:%s", "XX"));
				break;
			default:
				break;
			}
		}
		//for (Vector<Sprite*>::iterator iter = goodsSprites.begin(); iter != goodsSprites.end(); iter++)
		//{
		//	*iter = NULL;
		//}
		if (difficultyLevel < maxDifficultyLevel){
			difficultyLevel = scoreNumber / 5000 + 1;
			levelLabel->setString(StringUtils::format("level:%d", difficultyLevel));
		}
		if (cargoCount < 5){
			if (cargoCount != (difficultyLevel/3 + 3)){
				cargoCount = difficultyLevel/3+3;

			}
		}
		//���߳���Ļ�����ٻ��������������
		train->removeFromParentAndCleanup(true);
		selSprite = NULL;
		touchSprite = NULL;
		for (int i = 0; i < goodsSprites.size(); i++){ 
			goodsSprites.at(i)->removeFromParentAndCleanup(true);
			
		}
		for (int i = 0; i < carriageSprites.size(); i++){
			carriageSprites.at(i)->removeFromParentAndCleanup(true);
		}

		//�𳵸ı��ٶ����¿��������Ｐ�������¼���
		if(t<=5.0f)
		{t += 0.25; }
		createTrain(5);
		createGoodsAndCarriage(1,cargoCount);
	}
	return true;
}
void GameScene::createTrain(int number){
	train = Sprite::create("u8.png");
	train->setScale((winSize.height/train->getContentSize().height)*0.16f);
	trainWidth = train->getContentSize().width*train->getScale();
	trainHorizon = winSize.height / 4.0f;
	firstCargo = 0.188f*trainWidth;
	cargoOffset = 0.153f*trainWidth;
	//train->setAnchorPoint(Point(train->getContentSize().width*train->getScale()*0.5f, train->getContentSize().height*train->getScale()*0.5f));
	train->setPosition(Point(-train->getContentSize().width/2.0f, winSize.height/4.0f));
	trainMove = MoveBy::create(20.0 - t, Point(winSize.width + trainWidth+cargoOffset, 0));
	train->runAction(trainMove);
	SimpleAudioEngine::getInstance()->playEffect("effects/train.mp3");
	Background->addChild(train, 10);
}

//��������
bool GameScene::onTouchBegan(Touch* ptouch, Event* pevent){
	selSprite = NULL;
	touchSprite = NULL;
	Point touchLocation = this->convertTouchToNodeSpace(ptouch);
	this->selectSpriteForTouch(touchLocation);

	return true;
}
void GameScene::onTouchMoved(Touch* ptouch, Event* pevent){
	Point touchLocation = this->convertTouchToNodeSpace(ptouch);
	Point oldTouchLocation = ptouch->getPreviousLocation();
	Point translation = touchLocation - oldTouchLocation;
	this->panForTranslation(translation);
}
void GameScene::onTouchEnded(Touch* ptouch, Event* pevent){
	Point touchLocation = this->convertTouchToNodeSpace(ptouch);
	this->selectSpriteTouching(touchLocation);
	if (selSprite!=NULL&&touchSprite!=NULL){
		if (selSprite->getName()==touchSprite->getName()){
		selSprite->removeFromParentAndCleanup(true);
		carriageSprites.eraseObject(selSprite, true);
		//auto blink = Blink::create(1,3);
		auto colorChange = TintTo::create(0.1f,Color3B::WHITE);
		touchSprite->runAction(colorChange);
		scoreNumber += scoreOnce;
		score->setString(StringUtils::format("score:%d", scoreNumber));
		selSprite = NULL;
		touchSprite = NULL;
	    }
		else{
			selSprite->stopAllActions();
			auto moveToFirstPlace = MoveTo::create(0.5f, selSprite->getSpritePosition());
			//selSprite->runAction(moveToFirstPlace);
			//auto changColor = TintTo::create(0, Color3B::WHITE);
			//selSprite->runAction(changColor);
			auto Smaller = ScaleTo::create(0,2.0/3.0);
			auto seq = Sequence::create(moveToFirstPlace,Smaller,NULL);
			selSprite->runAction(seq);
		}
	}
	else{
		if (selSprite != NULL)
		{		
			    selSprite->stopAllActions();
			    auto moveToFirstPlace = MoveTo::create(0.5f, selSprite->getSpritePosition());
		        //selSprite->runAction(moveToFirstPlace);
				//auto changColor = TintTo::create(0, Color3B::WHITE);
				//selSprite->runAction(changColor);
				auto Smaller = ScaleTo::create(0,2.0/3.0);
				auto seq = Sequence::create(moveToFirstPlace, Smaller,NULL);
				selSprite->runAction(seq);
	}
	}

}
void GameScene::selectSpriteForTouch(Point touchLocation)
{
	RoleSprite * newSprite = NULL;
	for (RoleSprite *sprite : carriageSprites)
	{
		if (sprite->getBoundingBox().containsPoint(touchLocation))
		{
			//SpriteFirstPosition = sprite->getPosition();
			newSprite = sprite;
			break;
		}
	}
	if ( NULL != newSprite)
	{
		selSprite = newSprite;
		auto Bigger = ScaleTo::create(0,1.5f);
		selSprite->runAction(Bigger);
		//auto changColor = TintTo::create(0.1f, Color3B::RED);
		//selSprite->runAction(changColor);
		SimpleAudioEngine::getInstance()->playEffect("effects/star.wav");
	}
}
	Point GameScene::boundLayerPos(Point newPos)
	{
		Size winSize = Director::getInstance()->getWinSize();
		Point retval = newPos;

		retval.x = MIN(retval.x, 0);
		retval.x = MAX(retval.x, winSize.width + winSize.width);

		retval.y = this->getPosition().y;
		return retval;
	}

	void GameScene::panForTranslation(Point translation)
	{
		if (selSprite!=NULL)
		{
			Point newPos = selSprite->getPosition() + translation;
			selSprite->setPosition(newPos);
		}
		//else
		//{
		//	Point newPos = this->getPosition() + translation;
		//	this->setPosition(this->boundLayerPos(newPos));
		//}
	}
	void GameScene::selectSpriteTouching(Point touchLocation){
		Sprite * newSprite = NULL;
		for (Sprite *sprite : goodsSprites)
		{
			float goodScale = 0.2f;
			Rect goodRect = CCRectMake(sprite->getPositionX()-winSize.width*train->getScale()*goodScale/2.0f,
				sprite->getPositionY()-winSize.height*train->getScale()*goodScale/2.0f,
				winSize.width*train->getScale()*goodScale,
				winSize.height*train->getScale()*goodScale);
			if (goodRect.containsPoint(touchLocation))
			{
				newSprite = sprite;

				break;
			}
		}
		if (newSprite != touchSprite && NULL != newSprite)
		{
			touchSprite = newSprite;
		}
	}


	void GameScene::loadVoice(){
		//���ض�Ӧ����
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic("effects/BGM_1.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("effects/train.mp3");
		SimpleAudioEngine::getInstance()->preloadEffect("effects/star.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("effects/lose.mp3");
		SimpleAudioEngine::getInstance()->preloadEffect("effects/ao.wav");
	}
	void GameScene::pauseCallBack(Ref* pObjcet){
		pauseButton->setEnabled(false);
		_eventDispatcher->pauseEventListenersForTarget(this);
		//����1Ϊ��ͣ�˵�
		loadMenu(1);
		Director::getInstance()->pause();
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		//Director::getInstance()->resume();
	}
	void GameScene::loadMenu(int pauseOrGameOver){
		auto layer = Layer::create();
		this->addChild(layer, 99);
		MenuItemImage *menuBackGround = MenuItemImage::create("icon/menu.png", "icon/menu.png");
		MenuItemImage *retryTheGame = MenuItemImage::create("icon/retrynormal.png", "icon/retryclick.png", CC_CALLBACK_1(GameScene::retryCallBack, this));
		MenuItemImage *returnToGameSelectScene = MenuItemImage::create("icon/menunormal.png", "icon/menuclick.png", CC_CALLBACK_1(GameScene::returnToGameSelect, this));
		menuBackGround->setPosition(winSize.width / 2, winSize.height / 2);
		menuBackGround->setScale(0.8f);
		retryTheGame->setPosition(Point(winSize.width / 2 - 100, winSize.height / 2));
		retryTheGame->setScale(0.3f);
		returnToGameSelectScene->setPosition(Point(winSize.width / 2, winSize.height / 2));
		returnToGameSelectScene->setScale(0.3f);
		if (pauseOrGameOver == 1){
			MenuItemImage *resumeTheGame = MenuItemImage::create("icon/returnnormal.png", "icon/returnclick.png", CC_CALLBACK_1(GameScene::resumeTheGame, this));
			resumeTheGame->setPosition(Point(winSize.width / 2 + 100, winSize.height / 2));
			resumeTheGame->setScale(0.3f);
			pausemenu = Menu::create(menuBackGround, retryTheGame, returnToGameSelectScene, resumeTheGame, NULL);
		}
		else if (pauseOrGameOver == 2){
			MenuItemImage *nextGame = MenuItemImage::create("icon/next_normal.png", "icon/next_click.png", CC_CALLBACK_1(GameScene::nextGame, this));
			nextGame->setPosition(Point(winSize.width / 2 + 100, winSize.height / 2));
			nextGame->setScale(0.3f);
			pausemenu = Menu::create(menuBackGround, retryTheGame, returnToGameSelectScene, nextGame, NULL);
		}
		//pausemenu->alignItemsInRows(40);
		pausemenu->setPosition(Point(0, 0));
		layer->addChild(pausemenu, 100);
	}
	void GameScene::GameOverMenu(){
		//����2Ϊ��Ϸ�����˵�
		Director::getInstance()->pause();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->stopAllEffects();
		loadMenu(2);
	}
	void GameScene::retryCallBack(Ref* pObjcet){
		Director::getInstance()->resume();
		auto scene = GameScene::createScene(tollGate);
		Director::getInstance()->getRunningScene()->removeAllChildrenWithCleanup(true);
		Director::getInstance()->replaceScene(scene);
		//Director::getInstance()->popScene();
		//Director::getInstance()->pushScene(scene);
	}
	void GameScene::resumeTheGame(Ref* pObject){
		pauseButton->setEnabled(true);
		pausemenu->removeFromParentAndCleanup(true);
		_eventDispatcher->resumeEventListenersForTarget(this);
		//_eventDispatcher->setEnabled(true);
		Director::getInstance()->resume();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	void GameScene::returnToGameSelect(Ref* pObject){
		auto scene = SplashScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	void GameScene::nextGame(Ref* pObject){

	}
	void GameScene::setTollParameter(int tollGate, string const&filepath){
		this->tollGate = tollGate;
		this->backgroundFilePath = filepath;
	}