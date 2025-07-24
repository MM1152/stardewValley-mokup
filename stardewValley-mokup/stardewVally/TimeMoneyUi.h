#pragma once
#include "GameObject.h"
class TimeMoneyUi : public GameObject
{
	enum class MoneyUiType
	{
		null,
		zero,
		one,
		two,
		three,
		four,
		five,
		six,
		seven,
		eight,
		nine,
	};

	enum class SeasonType
	{
		spring,
		summer,
		autumn,
		winter,
	};

	enum class WeatherType
	{
		lucidity,
		spring_wind,
		rain,
		storm,
		fall_wind,
		snow,
	};

protected:

	bool ampm = false;
	bool isTimer = true;

	sf::Sprite ui;
	std::string uiId = "graphics/시계.png";
	
	sf::Sprite weatherUi;
	std::string weatherUiId = "graphics/날씨.bmp";

	sf::Sprite seasonUi;
	std::string seasonUiId = "graphics/계절.bmp";

	//if money % 10 == 0~9 > if (money % 100 - money % 10) == 0~9 .... 
	int money;
	int currentmoney;
	int n1;
	int n2;
	int n3;
	int n4;
	int n5;
	int n6;
	int n7;
	int n8;

	MoneyUiType mtype = MoneyUiType::null;
	sf::Sprite moneyUi;
	std::string moneyUiId = "graphics/돈 숫자.png";

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
	float minuteMaxTimer = 0.1f;

	

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

	void isTime();

	void ChangeAm()
	{
		ampm = false;
	}
	void ChangePm()
	{
		ampm = true;
	}

	void DrawMoney(int m);
};

