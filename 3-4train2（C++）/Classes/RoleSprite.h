#pragma once
#include<cocos2d.h>
using namespace std;
USING_NS_CC;
class RoleSprite:public Sprite
{
private:
	string touchMusic;
	string matchMusic;
	Point SpritePosition;
public:
	RoleSprite();
	virtual ~RoleSprite();
	void setTouchMusic(string &filepath);
	string getTouchMusic();
	void setMatchMusic(string &filepath);
	string getMatchMusic();
	static RoleSprite* create(const std::string &modelPath);
	void setSpritePosition(Point const& position);
	Point getSpritePosition();
};

