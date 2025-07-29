#include "stdafx.h"
#include "Gatherable.h"

Gatherable::Gatherable(const std::string& name)
	: GameObject(name)
	, GtId("")
	, GtName("")
	, GtTextureId("")
	, uiTextCoord(-1, -1, -1, -1)
	, textureCoord(-1, -1, -1, -1)
	, interaction(false)
{
}


void Gatherable::Init()
{
}

void Gatherable::Release()
{
}

void Gatherable::Reset()
{
	GtSp.setTexture(TEXTURE_MGR.Get(GtTextureId));
}

void Gatherable::Update(float dt)
{
}

void Gatherable::Draw(sf::RenderWindow& window)
{
	window.draw(GtSp);
}

void Gatherable::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	GtSp.setPosition(pos);
}

void Gatherable::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	GtSp.setRotation(rot);
}

void Gatherable::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	GtSp.setScale(s);
}

void Gatherable::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	GtSp.setOrigin(o);
}

void Gatherable::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(GtSp, preset);
	}
}

void Gatherable::SetGtInfo(Gatherable* gatherable)
{
	{
		this->GtId = gatherable->GtId;
		this->GtName = gatherable->GtName;
		this->GtTextureId = gatherable->GtTextureId;
		this->uiTextCoord = gatherable->uiTextCoord;
		this->textureCoord = gatherable->textureCoord;
		this->interaction = gatherable->interaction;
		Reset();
	}
}
