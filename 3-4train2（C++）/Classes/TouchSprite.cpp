#include "TouchSprite.h"


TouchSprite::TouchSprite()
{
}
TouchSprite::~TouchSprite()
{
}

Rect TouchSprite::getRect()
{
	  auto s = this->getContentSize();
	  return Rect(-s.width / 2, -s.height / 2, s.width/2, s.height/2);
	
}

void TouchSprite::onEnter()
{
	 Sprite::onEnter();
	    // Register Touch Event   
     auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(TouchSprite::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TouchSprite::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchSprite::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); 
	_state = kPaddleStateUngrabbed;
	FirstPosition=this->getPosition();
	}

void TouchSprite::onExit()
{
	    //    auto director = Director::getInstance();   
		    //    director->getTouchDispatcher()->removeDelegate(this);   
		    Sprite::onExit();
	}

bool TouchSprite::containsTouchLocation(Touch* touch)
{
    //return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));   
		    float len = (this->getPosition() - touch->getLocation()).length();
         if (len < 150){  return true;}
	    return false;
}

bool TouchSprite::onTouchBegan(Touch* touch, Event* event)
{
	    //CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
	
		if (_state != kPaddleStateUngrabbed) return false;
	    if (!containsTouchLocation(touch)) return false;
	    m_oldPoint = touch->getLocation();
	    _state = kPaddleStateGrabbed;
	   // CCLOG("return true");
	   return true;
	}

void TouchSprite::onTouchMoved(Touch* touch, Event* event)
{
	    // If it weren't for the TouchDispatcher, you would need to keep a reference   
		    // to the touch from touchBegan and check that the current touch is the same   
		    // as that one.   
		    // Actually, it would be even more complicated since in the Cocos dispatcher   
		    // you get Sets instead of 1 UITouch, so you'd need to loop through the set   
		    // in each touchXXX method.   
		
	   //CCLOG("Paddle::onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
       CCASSERT(_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");
	
	   auto touchPoint = touch->getLocation();
	   
		    //setPosition( Vec2(touchPoint.x, getPosition().y) );   
	   setPosition(this->getPosition() + touchPoint - m_oldPoint);
	   m_oldPoint = touchPoint;
	}

void TouchSprite::onTouchEnded(Touch* touch, Event* event)
{
	   this->getPhysicsBody()->setContactTestBitmask(getBitmask());
	   this->getPhysicsBody()->setCollisionBitmask(getBitmask());
	   this->getPhysicsBody()->setCategoryBitmask(getBitmask());
       CCASSERT(_state == kPaddleStateGrabbed, "Paddle - Unexpected state!");
	   _state = kPaddleStateUngrabbed;
	   auto moveAction = MoveTo::create(0.5,FirstPosition);
	   this->runAction(moveAction);

	   //setPosition(FirstPosition);
	}
TouchSprite* TouchSprite::create(const std::string &modelPath)
{
	    TouchSprite* _obj = new TouchSprite();
	    _obj->autorelease();
	    _obj->initWithFile(modelPath);
		return _obj;
	}
void TouchSprite::setBitmask(int bitmask){
	this->bitmask = bitmask;
}
int TouchSprite::getBitmask(){
	return bitmask;
}
//void TouchSprite::setPosition(const Vec2&position){
	
//}

