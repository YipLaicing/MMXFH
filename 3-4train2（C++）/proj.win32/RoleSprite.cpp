#include "RoleSprite.h"

void RoleSprite::setTouchMusic(string &filepath){
	this->touchMusic = filepath;
}
string RoleSprite::getTouchMusic(){
	return this->touchMusic;
}
void RoleSprite::setMatchMusic(string &filepath){
	this->matchMusic = filepath;
}
string RoleSprite::getMatchMusic(){
	return this->matchMusic;
}
RoleSprite* RoleSprite::create(const std::string &modelPath){
	RoleSprite* _obj = new RoleSprite();
	_obj->autorelease();
	_obj->initWithFile(modelPath);
	return _obj;
}
RoleSprite::RoleSprite()
{
}
RoleSprite::~RoleSprite()
{
}
void RoleSprite::setSpritePosition(Point const& position){
	this->SpritePosition = position;
}
Point RoleSprite::getSpritePosition(){
	return this->SpritePosition;
}