#include "stdafx.h"
#include "Button.h"

Button::Button(const std::string fontId, const std::string texId, const std::string name)
	:GameObject(name)
	,fontId(fontId)
	,texId(texId)
{
}

void Button::Init()
{
	bnt.setFillColor(sf::Color::White);
}

void Button::Release()
{
}

void Button::Reset()
{
	
	text.setFont(FONT_MGR.Get(fontId));
	if (!texId.empty()) {
		bnt.setTexture(&TEXTURE_MGR.Get(texId));
	}
	else {
		//bnt.setSize({ 100.f, (float)text.getCharacterSize() });
	}

}

void Button::Update(float dt)
{
	if (InputMgr::GetMouseUIRect().intersects(bnt.getGlobalBounds())) {
		bnt.setFillColor(sf::Color(210, 180, 140));
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
			if (onClickFunc) {
				onClickFunc();
			}
		}
	}
	else {
		bnt.setFillColor(sf::Color::White);
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(bnt);
	window.draw(text);
}

void Button::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	bnt.setPosition(pos);
	text.setPosition(pos);
}

void Button::SetRotation(float rot)
{
	rotation = rot;
	bnt.setRotation(rot);
}

void Button::SetScale(const sf::Vector2f& s)
{
	scale = s;
	bnt.setScale(s);
}

void Button::SetOrigin(const sf::Vector2f& o)
{
	origin = o;
	originPreset = Origins::Custom;
	bnt.setOrigin(o);
}

void Button::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(bnt, preset);
}

void Button::SetString(const std::string word)
{
	text.setString(word);
	bnt.setSize({(float)word.size() * text.getCharacterSize() * 0.5f, (float)text.getCharacterSize() });
}

void Button::SetTextColor(sf::Color color)
{
	text.setFillColor(color);
}
