#include "stdafx.h"
#include "inputText.h"

InputText::InputText(const std::string& fontId, const std::string& texId, const std::string& name)
	:GameObject(name)
	,fontId(fontId)
	,texId(texId)
{
	sortingLayer = SortingLayers::UI;
}

void InputText::Init()
{
}

void InputText::Release()
{
}

void InputText::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	
	if (texId.empty()) {
		inputBoxInitSize = { 300.f , (float)text.getCharacterSize() };
		inputBox.setSize(inputBoxInitSize);
	}
	else {
		inputBox.setTexture(&TEXTURE_MGR.Get(texId));
	}
}

void InputText::Update(float dt)
{
	if (InputMgr::GetMouseUIRect().intersects(inputBox.getGlobalBounds())) {
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
			inputAble = true;
		}
	}
	else {
		inputAble = false;
	}

	if (inputAble) {
		if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace)) {
			if (input.size() > 0) input.resize(input.size() - 1);
		}
		else if(InputMgr::GetAnyKeyDown()){
			input += InputMgr::GetInputText();
		}
		SetString(input);
	}
}

void InputText::Draw(sf::RenderWindow& window)
{
	window.draw(inputBox);
	window.draw(text);
}

void InputText::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	inputBox.setPosition(pos);
	text.setPosition(pos);
}

void InputText::SetRotation(float rot)
{
	rotation = rot;
	inputBox.setRotation(rot);
	text.setRotation(rot);
}

void InputText::SetScale(const sf::Vector2f& s)
{
	scale = s;
	inputBox.setScale(s);
	text.setScale(s);
}

void InputText::SetOrigin(const sf::Vector2f& o)
{
	origin = o;
	originPreset = Origins::Custom;
	inputBox.setOrigin(o);
	text.setOrigin(o);
}

void InputText::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(inputBox , preset);
	Utils::SetOrigin(text, preset);
}

void InputText::SetTextColor(const sf::Color& color)
{
	text.setFillColor(color);
}

void InputText::SetSize(const sf::Vector2f& size)
{
	inputBox.setSize(size);
}

void InputText::SetString(const std::string text)
{
	this->text.setString(text);
	if (text.size() * this->text.getCharacterSize() * 0.5f >= inputBox.getSize().x) {
		inputBox.setSize({inputBoxInitSize.x + text.size() * this->text.getCharacterSize() * 0.5f, inputBox.getSize().y});
	}
	SetOrigin(originPreset);
}


