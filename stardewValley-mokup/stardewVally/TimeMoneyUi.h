#pragma once
#include "GameObject.h"

class Player;

class TimeMoneyUi : public GameObject
{
protected:

	bool ampm = false;
	bool isTimer = true;

	sf::Sprite ui;
	std::string uiId = "graphics/clock.png";

	//if money % 10 == 0~9 > if (money % 100 - money % 10) == 0~9 .... 
	int money;
	int currentmoney;
	int n1 = -1;
	int n2 = -1;
	int n3 = -1;
	int n4 = -1;
	int n5 = -1;
	int n6 = -1;
	int n7 = -1;
	int n8 = -1;


	sf::Sprite m1;
	sf::Sprite m2;
	sf::Sprite m3;
	sf::Sprite m4;
	sf::Sprite m5;
	sf::Sprite m6;
	sf::Sprite m7;
	sf::Sprite m8;

	std::string moneyUiId = "graphics/moneyFont.png";
	//rect

	//dom = day of week -> th % 7 -> 1 월 , 2 화 , 3 수 , 4 목, 5 금, 6 토, 0 일 / th > 28 {th = 1}
	//change season
	int th = 1;
	std::string isdow;
	sf::Text dow;
	std::string dowfont = "fonts/DOSGothic.ttf";


	//meridem -> change(am / pm) = hour = 12 -> hour > 12 (hour = 1) / mitute += 10 if(minute > 50){hour += 1) 
	int hour = 6;
	int minute = 0;
	std::string istime;
	sf::Text meridiem;
	std::string meridiemfont = "fonts/DOSGothic.ttf";

	float minuteTimer = 0.f;
	float minuteMaxTimer = 0.2f;

	Player* player;

public:
	TimeMoneyUi(const std::string& name = "");
	virtual ~TimeMoneyUi() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void ChangeAm()
	{
		ampm = false;
	}
	void ChangePm()
	{
		ampm = true;
	}

	void SettingMoney(int m);

	void ResetSettingMoney();

	void ChangeTimer()
	{
		isTimer = !isTimer;
	}

	void Changeth();

	void Setplayer(Player* player);
	Player* GetPlayer();

	void Sethour(int h)
	{
		hour = h;
		Scene::curHour = hour;
	}
	int Gethour()
	{
		return hour;
	}
	void Setminute(int m)
	{
		minute = m;
	}
	int Getminute()
	{
		return minute;
	}
	void Setth(int t)
	{
		th = t;
	}
	int Getth()
	{
		return th;
	}
};

