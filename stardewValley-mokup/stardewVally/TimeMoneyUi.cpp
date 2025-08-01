#include "stdafx.h"
#include "TimeMoneyUi.h"
#include "Player.h"
#include "Crops.h"

TimeMoneyUi::TimeMoneyUi(const std::string& name)
	: GameObject(name)
{
}

void TimeMoneyUi::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	ui.setPosition(pos);
}

void TimeMoneyUi::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	ui.setRotation(rot);
}

void TimeMoneyUi::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	ui.setScale(s);
}

void TimeMoneyUi::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	ui.setOrigin(o);
}

void TimeMoneyUi::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(ui, preset);
	}
}

void TimeMoneyUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	istime = Utils::TostringTime(hour, minute);
	meridiem.setPosition({ 1136.f, 80.f });
	meridiem.setFillColor(sf::Color::Black);

	isdow = Utils::TostringDOW(th);
	dow.setPosition({ 1160.f, 15.f });
	dow.setFillColor(sf::Color::Black);

	m1.setPosition({ 1235.f, 138.f });
	m2.setPosition({ 1218.f, 138.f });
	m3.setPosition({ 1201.f, 138.f });
	m4.setPosition({ 1184.f, 138.f });
	m5.setPosition({ 1167.f, 138.f });
	m6.setPosition({ 1150.f, 138.f });
	m7.setPosition({ 1133.f, 138.f });
	m8.setPosition({ 1116.f, 138.f });

	ampm = false;
	isTimer = true;
}

void TimeMoneyUi::Release()
{
}

void TimeMoneyUi::Reset()
{
	dowfont = "fonts/DOSGothic.ttf";
	meridiemfont = "fonts/DOSGothic.ttf";
	moneyUiId = "graphics/moneyFont.png";
	uiId = "graphics/clock.png";

	ui.setTexture(TEXTURE_MGR.Get(uiId));

	m1.setTexture(TEXTURE_MGR.Get(moneyUiId));
	m2.setTexture(TEXTURE_MGR.Get(moneyUiId));
	m3.setTexture(TEXTURE_MGR.Get(moneyUiId));
	m4.setTexture(TEXTURE_MGR.Get(moneyUiId));
	m5.setTexture(TEXTURE_MGR.Get(moneyUiId));
	m6.setTexture(TEXTURE_MGR.Get(moneyUiId));
	m7.setTexture(TEXTURE_MGR.Get(moneyUiId));
	m8.setTexture(TEXTURE_MGR.Get(moneyUiId));

	dow.setFont(FONT_MGR.Get(dowfont));
	dow.setString(isdow);


	meridiem.setFont(FONT_MGR.Get(meridiemfont));
	if (!ampm)
	{
		meridiem.setString(istime + "am");
	}
	else
	{
		meridiem.setString(istime + "pm");
	}

	SetScale({ 1.f, 1.f });
	SetOrigin(Origins::TR);
	SetPosition({ 1270.f, 10.f });
}

void TimeMoneyUi::Update(float dt)
{
	// Time
	if (isTimer && !player->GetFainting())
	{
		minuteTimer += dt;
		if (minuteTimer > minuteMaxTimer)
		{
			minute += 10;
			if (minute > 50)
			{
				minute = 0;
				hour += 1;
				if (hour == 12)
				{
					if (!ampm)
					{
						ChangePm();
					}
					else
					{
						ChangeAm();
						th += 1;

					}
				}
				else if (hour > 12)
				{
					hour = 1;
				}

				if (!ampm && hour == 2)
				{
					isTimer = false;
					player->ChangeFainting();
					player->SetIsPlayer(false);
				}
			}
			istime = Utils::TostringTime(hour, minute);
			isdow = Utils::TostringDOW(th);
			Reset();
			minuteTimer = 0;
		}
	}
}

void TimeMoneyUi::Draw(sf::RenderWindow& window)
{
	window.draw(ui);

	window.draw(m1);
	window.draw(m2);
	window.draw(m3);
	window.draw(m4);
	window.draw(m5);
	window.draw(m6);
	window.draw(m7);
	window.draw(m8);

	//window.draw(weatherUi);
	//window.draw(seasonUi);

	window.draw(dow);
	window.draw(meridiem);
}


void TimeMoneyUi::SettingMoney(int m)
{
	sf::IntRect null(0, 0, 0, 0);
	sf::IntRect zero(0, 0, 14, 20);
	sf::IntRect one(14, 0, 14, 20);
	sf::IntRect two(28, 0, 14, 20);
	sf::IntRect three(42, 0, 14, 20);
	sf::IntRect four(56, 0, 14, 20);
	sf::IntRect five(70, 0, 14, 20);
	sf::IntRect six(84, 0, 14, 20);
	sf::IntRect seven(98, 0, 14, 20);
	sf::IntRect eight(112, 0, 14, 20);
	sf::IntRect nine(126, 0, 14, 20);

	if (n1 < 0)
	{
		m1.setTextureRect(null);
	}
	if (n2 < 0)
	{
		m2.setTextureRect(null);
	}
	if (n3 < 0)
	{
		m3.setTextureRect(null);
	}
	if (n4 < 0)
	{
		m4.setTextureRect(null);
	}
	if (n5 < 0)
	{
		m5.setTextureRect(null);
	}
	if (n6 < 0)
	{
		m6.setTextureRect(null);
	}
	if (n7 < 0)
	{
		m7.setTextureRect(null);
	}
	if (n8 < 0)
	{
		m8.setTextureRect(null);
	}


	money = m;
	if (money >= 0)
	{
		n1 = money % 10;
		if (n1 == 0)
		{
			m1.setTextureRect(zero);
		}
		if (n1 == 1)
		{
			m1.setTextureRect(one);
		}
		if (n1 == 2)
		{
			m1.setTextureRect(two);
		}
		if (n1 == 3)
		{
			m1.setTextureRect(three);
		}
		if (n1 == 4)
		{
			m1.setTextureRect(four);
		}
		if (n1 == 5)
		{
			m1.setTextureRect(five);
		}
		if (n1 == 6)
		{
			m1.setTextureRect(six);
		}
		if (n1 == 7)
		{
			m1.setTextureRect(seven);
		}
		if (n1 == 8)
		{
			m1.setTextureRect(eight);
		}
		if (n1 == 9)
		{
			m1.setTextureRect(nine);
		}
	}
	if (money >= 10)
	{
		n2 = (money % 100 - money % 10) / 10;
		if (n2 == 0)
		{
			m2.setTextureRect(zero);
		}
		if (n2 == 1)
		{
			m2.setTextureRect(one);
		}
		if (n2 == 2)
		{
			m2.setTextureRect(two);
		}
		if (n2 == 3)
		{
			m2.setTextureRect(three);
		}
		if (n2 == 4)
		{
			m2.setTextureRect(four);
		}
		if (n2 == 5)
		{
			m2.setTextureRect(five);
		}
		if (n2 == 6)
		{
			m2.setTextureRect(six);
		}
		if (n2 == 7)
		{
			m2.setTextureRect(seven);
		}
		if (n2 == 8)
		{
			m2.setTextureRect(eight);
		}
		if (n2 == 9)
		{
			m2.setTextureRect(nine);
		}
	}
	if (money >= 100)
	{
		n3 = (money % 1000 - money % 100) / 100;
		if (n3 == 0)
		{
			m3.setTextureRect(zero);
		}
		if (n3 == 1)
		{
			m3.setTextureRect(one);
		}
		if (n3 == 2)
		{
			m3.setTextureRect(two);
		}
		if (n3 == 3)
		{
			m3.setTextureRect(three);
		}
		if (n3 == 4)
		{
			m3.setTextureRect(four);
		}
		if (n3 == 5)
		{
			m3.setTextureRect(five);
		}
		if (n3 == 6)
		{
			m3.setTextureRect(six);
		}
		if (n3 == 7)
		{
			m3.setTextureRect(seven);
		}
		if (n3 == 8)
		{
			m3.setTextureRect(eight);
		}
		if (n3 == 9)
		{
			m3.setTextureRect(nine);
		}
	}
	if (money >= 1000)
	{
		n4 = (money % 10000 - money % 1000) / 1000;
		if (n4 == 0)
		{
			m4.setTextureRect(zero);
		}
		if (n4 == 1)
		{
			m4.setTextureRect(one);
		}
		if (n4 == 2)
		{
			m4.setTextureRect(two);
		}
		if (n4 == 3)
		{
			m4.setTextureRect(three);
		}
		if (n4 == 4)
		{
			m4.setTextureRect(four);
		}
		if (n4 == 5)
		{
			m4.setTextureRect(five);
		}
		if (n4 == 6)
		{
			m4.setTextureRect(six);
		}
		if (n4 == 7)
		{
			m4.setTextureRect(seven);
		}
		if (n4 == 8)
		{
			m4.setTextureRect(eight);
		}
		if (n4 == 9)
		{
			m4.setTextureRect(nine);
		}
	}
	if (money >= 10000)
	{
		n5 = (money % 100000 - money % 10000) / 10000;
		if (n5 == 0)
		{
			m5.setTextureRect(zero);
		}
		if (n5 == 1)
		{
			m5.setTextureRect(one);
		}
		if (n5 == 2)
		{
			m5.setTextureRect(two);
		}
		if (n5 == 3)
		{
			m5.setTextureRect(three);
		}
		if (n5 == 4)
		{
			m5.setTextureRect(four);
		}
		if (n5 == 5)
		{
			m5.setTextureRect(five);
		}
		if (n5 == 6)
		{
			m5.setTextureRect(six);
		}
		if (n5 == 7)
		{
			m5.setTextureRect(seven);
		}
		if (n5 == 8)
		{
			m5.setTextureRect(eight);
		}
		if (n5 == 9)
		{
			m5.setTextureRect(nine);
		}
	}
	if (money >= 100000)
	{
		n6 = (money % 1000000 - money % 100000) / 100000;
		if (n6 == 0)
		{
			m6.setTextureRect(zero);
		}
		if (n6 == 1)
		{
			m6.setTextureRect(one);
		}
		if (n6 == 2)
		{
			m6.setTextureRect(two);
		}
		if (n6 == 3)
		{
			m6.setTextureRect(three);
		}
		if (n6 == 4)
		{
			m6.setTextureRect(four);
		}
		if (n6 == 5)
		{
			m6.setTextureRect(five);
		}
		if (n6 == 6)
		{
			m6.setTextureRect(six);
		}
		if (n6 == 7)
		{
			m6.setTextureRect(seven);
		}
		if (n6 == 8)
		{
			m6.setTextureRect(eight);
		}
		if (n6 == 9)
		{
			m6.setTextureRect(nine);
		}
	}
	if (money >= 1000000)
	{
		n7 = (money % 10000000 - money % 1000000) / 1000000;
		if (n7 == 0)
		{
			m7.setTextureRect(zero);
		}
		if (n7 == 1)
		{
			m7.setTextureRect(one);
		}
		if (n7 == 2)
		{
			m7.setTextureRect(two);
		}
		if (n7 == 3)
		{
			m7.setTextureRect(three);
		}
		if (n7 == 4)
		{
			m7.setTextureRect(four);
		}
		if (n7 == 5)
		{
			m7.setTextureRect(five);
		}
		if (n7 == 6)
		{
			m7.setTextureRect(six);
		}
		if (n7 == 7)
		{
			m7.setTextureRect(seven);
		}
		if (n7 == 8)
		{
			m7.setTextureRect(eight);
		}
		if (n7 == 9)
		{
			m7.setTextureRect(nine);
		}
	}
	if (money >= 10000000)
	{
		n8 = (money % 100000000 - money % 10000000) / 10000000;
		if (n8 == 0)
		{
			m8.setTextureRect(zero);
		}
		if (n8 == 1)
		{
			m8.setTextureRect(one);
		}
		if (n8 == 2)
		{
			m8.setTextureRect(two);
		}
		if (n8 == 3)
		{
			m8.setTextureRect(three);
		}
		if (n8 == 4)
		{
			m8.setTextureRect(four);
		}
		if (n8 == 5)
		{
			m8.setTextureRect(five);
		}
		if (n8 == 6)
		{
			m8.setTextureRect(six);
		}
		if (n8 == 7)
		{
			m8.setTextureRect(seven);
		}
		if (n8 == 8)
		{
			m8.setTextureRect(eight);
		}
		if (n8 == 9)
		{
			m8.setTextureRect(nine);
		}
	}
}

void TimeMoneyUi::ResetSettingMoney()
{
	n1 = -1;
	n2 = -1;
	n3 = -1;
	n4 = -1;
	n5 = -1;
	n6 = -1;
	n7 = -1;
	n8 = -1;
}

void TimeMoneyUi::Changeth()
{
	if (!ampm && hour <= 2 || !ampm && hour == 12)
	{
		hour = 6;
		minute = 0;
		isTimer = true;
	}
	else
	{
		th += 1;
		hour = 6;
		minute = 0;
		isTimer = true;
		if (th > 28)
		{
			th = 1;
		}
	}
}

void TimeMoneyUi::Setplayer(Player* player)
{
	this->player = player;
}

Player* TimeMoneyUi::GetPlayer()
{
	return player;
}