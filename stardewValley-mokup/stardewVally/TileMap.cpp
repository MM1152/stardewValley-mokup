#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f texCoords[4] =
	{	
		{ 0.f, 0.f },
		{ size.x, 0.f },
		{ size.x, size.y },
		{ 0.f, size.y },
	};

	for (int i = 0; i < count.y; ++i)
	{
		for (int j = 0; j < count.x; ++j)
		{
			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(j * size.x, i * size.y);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + texCoords[k];
				va[vertexIndex].texCoords = {texCoords[k].x + j * size.x , texCoords[k].y + i * size.y};
			}
		}
	}
}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void TileMap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}
	UpdateTransform();
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);

	SetOrigin(Origins::MC);
	SetScale({ 1.f, 1.f });
	SetPosition({ 0.f, 0.f });
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);	
	window.draw(grid, state);
}
void TileMap::drawGrid(const sf::Vector2i& count, const sf::Vector2f& size)
{
	int numLines = count.x + count.y - 2;

	grid.clear();
	grid.setPrimitiveType(sf::Lines);
	grid.resize(2 * numLines);

	float rowH = size.x;
	float colW = size.y;

	// row separators
	for (int i = 0; i < count.x - 1; i++)
	{
		int r = i + 1;
		float rowY = rowH * r;
		grid[i * 2].position = { 0, rowY };
		grid[i * 2 + 1].position = { size.x * count.y, rowY };
	}
	// column separators
	for (int j = count.x - 1; j < numLines; j++)
	{
		int c = j - count.x + 2;
		float colX = colW * c;
		grid[j * 2].position = { colX, 0 };
		grid[j * 2 + 1].position = { colX, size.y * count.x };
	}
}