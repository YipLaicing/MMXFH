#pragma once
#include<iostream>
#include "cocos2d.h"
#include "time.h"
#include"cmath"
USING_NS_CC;
using namespace std;
class SpriteResource
{
	int m_tollGate;
	int m_number;
	vector<string> m_SpriteSource;
public:
	SpriteResource();
	virtual ~SpriteResource();
	//��ž��鼰��������
	vector<string> getResource(int tollGate, int number);
	void setTollGate(int tollGate);
	int getTollGate();
	void setNumber(int number);
	int getNumber();
	void setSpriteSource(const vector<string>& SpriteSource);
	vector<string> getSpriteSource();
};

