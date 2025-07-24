#include "stdafx.h"
#include "TimeMoneyUi.h"

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

	ampm = false;
	isTimer = true;
}

void TimeMoneyUi::Release()
{
}

void TimeMoneyUi::Reset()
{
	ui.setTexture(TEXTURE_MGR.Get(uiId));
	moneyUi.setTexture(TEXTURE_MGR.Get(moneyUiId));
	weatherUi.setTexture(TEXTURE_MGR.Get(weatherUiId));
	seasonUi.setTexture(TEXTURE_MGR.Get(seasonUiId));

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
	if (isTimer)
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
					//player fainting change
				}
			}
			istime = Utils::TostringTime(hour, minute);
			isdow = Utils::TostringDOW(th);
			Reset();
			minuteTimer = 0;
		}
	}

	//Money
}

void TimeMoneyUi::Draw(sf::RenderWindow& window)
{
	window.draw(ui);
	window.draw(moneyUi);
	window.draw(weatherUi);
	window.draw(seasonUi);
	window.draw(dow);
	window.draw(meridiem);
}

void TimeMoneyUi::isTime()
{

}
