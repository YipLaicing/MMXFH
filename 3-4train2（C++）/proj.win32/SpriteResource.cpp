#include "SpriteResource.h"

SpriteResource::SpriteResource(){	
	
}
SpriteResource::~SpriteResource(){}
vector<string> SpriteResource::getResource(int tollGate,int number){
	m_SpriteSource.clear();
	switch (tollGate)
	{
	   
	   case 1:{
	    string Source[5] = {
		"u11.png",
		"u14.png",
		"u17.png",
		"u20.png",
		"u23.png",
	       };
		srand((unsigned)time(NULL));
		for (int i = 0; i < 5; i++){ int j = rand() % 5; swap(Source[i], Source[j]); }
		  for (int i = 0; i < number; i++){		 
			  m_SpriteSource.push_back(Source[i]);
		  }
		  break;
	   }
	   case 2:{break; }
	   default:
	          { break; }
	}
	return m_SpriteSource;
}
void SpriteResource::setTollGate(int tollGate){ this->m_tollGate = tollGate; }
int SpriteResource::getTollGate(){ return m_tollGate; }
void SpriteResource::setNumber(int number){ this->m_number = number; }
int SpriteResource::getNumber(){ return m_number; }
void SpriteResource::setSpriteSource(const vector<string>& SpriteSource){ this->m_SpriteSource = SpriteSource; }
vector<string> SpriteResource::getSpriteSource(){ return m_SpriteSource; }