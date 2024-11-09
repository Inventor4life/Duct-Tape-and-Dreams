#pragma once
#include "mainheader.h"

template <class OSTYPE>
class OnScreenText
{
public:
	
	OnScreenText() {// DEFAULT CONSTRUCTOR

		this->mPosX = -50.0f;
		this->mPosY = -50.0f;
		this->mText.setCharacterSize(10);
		this->mText.setString("0");
	}
	OnScreenText(int posX, int posY, int size, std::string text, OSTYPE data) {// COPY CONSTRUCTOR
		this->mPosX = posX;
		this->mPosY = posY;
		this->mText.setCharacterSize(size);
		this->mText.setString(text);
		this->mData = data;
	}

	~OnScreenText();

	// -----START SETTERS-----
	void setPosX(int newX) {
		this->mPosX = newX;
	}
	//	 ---setter: SET Y-----
	void setPosY(int newY) {
		this->mPosY = newY;
	}
	//	 ---setter: SET X-----
	void setFontSize(int newSize) {
		this->mText.setCharacterSize(newSize);
	}
	//	 ---setter: SET Text--
	void setText(std::string newText) {
		this->mText.setString(newText);
	}
	//	 ---setter: SET Data--
	void setData(OSTYPE newData) {
		this->mData = newData;
	}
	// -----END SETTERS------

	// ----BEGIN METHODS-----
	// 
	// ------END METHODS-----

private:
	/*
	I'm wondering since position is included in the sf::Text type if I even need these
	this is an early crappy testing scheme just so i can display things, not really worried
	about the actualy proper design, but just the crude function of it.
	I will revist this desing later
	--COMENT MADE: 11.8.24 @ 8:22p
	*/
	int mPosX;
	int mPosY;

	OSTYPE mData;
	sf::Text mText;
};