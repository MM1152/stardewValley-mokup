#include "stdafx.h"
#include "TileMap.h"
#include "rapidcsv.h"

TileMap::TileMap(VertexType type, const std::string& name)
	:GameObject(name)
	,type(type)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size , const std::string texId)
{
	texture = &TEXTURE_MGR.Get(texId);
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
				//va[vertexIndex].texCoords = { texCoords[k].x + j * size.x , texCoords[k].y + i * size.y };
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

}
//16.9
//4.3
void TileMap::Update(float dt){
	
	if (type == VertexType::Palette) 
	{
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && InArea((sf::Vector2f)InputMgr::GetMousePosition())) {
			int xIndex = (int)((int)(InputMgr::GetMousePosition().x - GetPosition().x)) / 16 * 4;
			int yIndex = (int)((int)(InputMgr::GetMousePosition().y - GetPosition().y)) / 16 * 4;
			index = xIndex + cellCount.x * yIndex;

			if (index >= cellCount.x * cellCount.y * 4) index = -1;

			if (getIndexFunc && index != -1) {
				sf::Vector2f texcoor[4];
				texcoor[0] = va[index].texCoords;
				texcoor[1] = va[index + 1].texCoords;
				texcoor[2] = va[index + 2].texCoords;
				texcoor[3] = va[index + 3].texCoords;

				getIndexFunc(texcoor);
			}
		}
	}

	if (type == VertexType::Draw) 
	{
		if (InputMgr::GetMouseButton(sf::Mouse::Left) && InArea((sf::Vector2f)InputMgr::GetMousePosition())) {
			int xIndex = (int)((int)(InputMgr::GetMousePosition().x - GetPosition().x)) / 16 * 4;
			int yIndex = (int)((int)(InputMgr::GetMousePosition().y - GetPosition().y)) / 16 * 4;
			index = xIndex + cellCount.x * yIndex;

			if (index >= cellCount.x * cellCount.y * 4) index = -1;

			if (setTextCoorFunc) {
				sf::Vector2f* texCoor = setTextCoorFunc();

				va[index].texCoords = texCoor[0];
				va[index + 1].texCoords = texCoor[1];
				va[index + 2].texCoords = texCoor[2];
				va[index + 3].texCoords = texCoor[3];
				std::cout << texCoor[0].x << ", " << texCoor[0].y << std::endl;
				std::cout << texCoor[1].x << ", " << texCoor[1].y << std::endl;
				std::cout << texCoor[2].x << ", " << texCoor[2].y << std::endl;
				std::cout << texCoor[3].x << ", " << texCoor[3].y << std::endl;

				std::to_string(va[index].texCoords.x);
				std::to_string(va[index+1].texCoords.x);
				std::to_string(va[index+2].texCoords.x);
				std::to_string(va[index+3].texCoords.x);

				std::to_string(va[index].texCoords.y);
				std::to_string(va[index+1].texCoords.y);
				std::to_string(va[index+2].texCoords.y);
				std::to_string(va[index+3].texCoords.y);

			}
		}
	}
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);	
}
 
void TileMap::drawGrid(const sf::Vector2i& count, const sf::Vector2f& size) {
	int numLines = count.x + 1 + count.y + 1;
    va.setPrimitiveType(sf::Lines);
	va.clear();
	va.resize(numLines * 2);
	
    for(int i=0; i < count.x + 1; i++){
		float rowX = size.x * (i);
        float rowY = size.y * count.y;
        va[i*2].position = {rowX, 0};
		va[i * 2].color = sf::Color::Green;
        va[i*2+1].position = {rowX , rowY};
		va[i * 2 + 1].color = sf::Color::Green;
    }

	for (int i = 0; i < count.y + 1; i++) {
		int curIdx = count.x + 1 + i;
		float colX = size.x * count.x;
		float colY = size.y * (i);

		va[curIdx * 2].position = { 0 , colY };
		va[curIdx * 2].color = sf::Color::Green;
		va[curIdx * 2 + 1].position = { colX , colY };
		va[curIdx * 2 + 1].color = sf::Color::Green;
	}	
}

bool TileMap::InArea(sf::Vector2f mousePos)
{	
	bool left = mousePos.x - (va.getBounds().left + GetPosition().x) > 0;
	bool right = mousePos.x - (va.getBounds().width + GetPosition().x) < 0;
	bool top = mousePos.y - (va.getBounds().top + GetPosition().y) > 0;
	bool height = mousePos.y - (va.getBounds().height + GetPosition().y) < 0;

	return left && right && top && height;
}
