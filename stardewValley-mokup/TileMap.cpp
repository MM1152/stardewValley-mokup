#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
{
}

void TileMap::Set(const sf::Vector2i& cellCount, const sf::Vector2f& cellSize)
{
	this->cellCount = cellCount;
	this->cellSize = cellSize;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(this->cellCount.x * this->cellCount.y * 4);

	sf::Vector2f posOffset[4] = {
		{0.f, 0.f,},
		{this->cellSize.x, 0.f},
		{this->cellSize.x , this->cellSize.y},
		{0.f , this->cellSize.y},
	};

	sf::Vector2f texCoords[4] = {
		{0.f, 0.f,},
		{50.f, 0.f},
		{50.f, 50.f},
		{0.f , 50.f},
	};

	for (int i = 0; i < this->cellCount.y; i++) {
		for (int j = 0; j < this->cellCount.x; j++) {
			int texIdx = Utils::RandomRange(0, 3);
			if (i == 0 || i == this->cellCount.y - 1 || j == 0 || j == this->cellCount.x - 1) {
				texIdx = 3;
			}

			int quadIndex = i * this->cellCount.x + j;
			sf::Vector2f quadPos(j * this->cellSize.x , i * this->cellSize.y);
			
			for (int k = 0; k < 4; k++) {
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + posOffset[k];
				va[vertexIndex].texCoords = texCoords[k];
				va[vertexIndex].texCoords.y += texIdx * 50;
			}
		}
	}
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	UpdateTransform();
}

void TileMap::SetRotation(float rot)
{
	rotation = rot;
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& o)
{
	origin = o;
	UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (preset != Origins::Custom) {
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)originPreset % 3) * 0.5f;
		origin.y = rect.height * ((int)originPreset / 3) * 0.5f;
	}

	UpdateTransform();
}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity; // 다 1 인 친구들
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::BackGround;
	sortingOrder = 0;

	Set({ 50,50 }, { 50.f,50.f });
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetid);
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va , state);
}
