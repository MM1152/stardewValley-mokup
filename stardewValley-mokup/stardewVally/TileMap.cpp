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
	cellData.clear();
	texture = &TEXTURE_MGR.Get(texId);
	spriteSheetId = texId;
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
			CellData cell;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + texCoords[k];
				va[vertexIndex].texCoords = {texCoords[k].x + j * size.x , texCoords[k].y + i * size.y};

				cell.cellPosition[k] = va[vertexIndex].position;
				cell.cellTextCoord[k] = va[vertexIndex].texCoords;
				cell.idx = quadIndex;
			}
			cellData.push_back(cell);
		}
	}

}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellData.clear();
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
			CellData cell;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + texCoords[k];
				va[vertexIndex].color = sf::Color::Transparent;

				cell.cellPosition[k] = va[vertexIndex].position;
				cell.cellColor[k] = va[vertexIndex].color;
				//va[vertexIndex].texCoords = { texCoords[k].x + j * size.x , texCoords[k].y + i * size.y };
			}
			cellData.push_back(cell);
		}
	}	
}

void TileMap::Set(const std::string texId, std::vector<CellData>& cellData)
{
	std::cout << texId << std::endl;
	this->va.clear();
	this->va.resize(cellData.size() * 4);
	this->va.setPrimitiveType(sf::Quads);
	
	for (int i = 0; i < cellData.size(); i++) {
		va[i * 4].texCoords = cellData[i].cellTextCoord[0];
		va[i * 4 + 1].texCoords = cellData[i].cellTextCoord[1];
		va[i * 4 + 2].texCoords = cellData[i].cellTextCoord[2];
		va[i * 4 + 3].texCoords = cellData[i].cellTextCoord[3];

		va[i * 4].position = cellData[i].cellPosition[0];
		va[i * 4 + 1].position = cellData[i].cellPosition[1];
		va[i * 4 + 2].position = cellData[i].cellPosition[2];
		va[i * 4 + 3].position = cellData[i].cellPosition[3];
	}

	texture = &TEXTURE_MGR.Get(texId);
}

void TileMap::SettingCellData(int idx , CellData cellData)
{
	this->cellData[idx] = cellData;
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
	
	/*if (type == VertexType::Palette) 
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
		if (InputMgr::GetMouseButton(sf::Mouse::Left) && InArea(scene->ScreenToWorld(InputMgr::GetMousePosition()))) {
			int xIndex = (int)((int)(scene->ScreenToWorld(InputMgr::GetMousePosition()).x - GetPosition().x)) / 16 * 4;
			int yIndex = (int)((int)(scene->ScreenToWorld(InputMgr::GetMousePosition()).y - GetPosition().y)) / 16 * 4;

			index = xIndex + cellCount.x * yIndex;

			if (index >= cellCount.x * cellCount.y * 4) index = -1;

			if (setTextCoorFunc) {
				sf::Vector2f* texCoor = setTextCoorFunc();
				
				if (texCoor[2].x == 0 && texCoor[2].y == 0) {
					va[index].color = sf::Color::Transparent;
					va[index + 1].color = sf::Color::Transparent;
					va[index + 2].color = sf::Color::Transparent;
					va[index + 3].color = sf::Color::Transparent;
					return;
				}

				va[index].color = sf::Color::White;
				va[index + 1].color = sf::Color::White;
				va[index + 2].color = sf::Color::White;
				va[index + 3].color = sf::Color::White;

				va[index].texCoords = texCoor[0];
				va[index + 1].texCoords = texCoor[1];
				va[index + 2].texCoords = texCoor[2];
				va[index + 3].texCoords = texCoor[3];
			}
		}
	}*/
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

void TileMap::SetTexture(const std::string texId)
{
	spriteSheetId = texId;
	texture = &TEXTURE_MGR.Get(texId);
}

void TileMap::SetCellData(int idx, CellData& celldata)
{
	if (celldata.idx == -1) {
		va[idx * 4].color = sf::Color::Transparent;
		va[idx * 4 + 1].color = sf::Color::Transparent;
		va[idx * 4 + 2].color = sf::Color::Transparent;
		va[idx * 4 + 3].color = sf::Color::Transparent;

		cellData[idx].idx = -1;
		return;
	}

	cellData[idx] = celldata;

	va[idx * 4].texCoords = cellData[idx].cellTextCoord[0];
	va[idx * 4 + 1].texCoords = cellData[idx].cellTextCoord[1];
	va[idx * 4 + 2].texCoords = cellData[idx].cellTextCoord[2];
	va[idx * 4 + 3].texCoords = cellData[idx].cellTextCoord[3];

	va[idx * 4].color = sf::Color::White;;
	va[idx * 4 + 1].color = sf::Color::White;
	va[idx * 4 + 2].color = sf::Color::White;
	va[idx * 4 + 3].color = sf::Color::White;
}

bool TileMap::InArea(sf::Vector2f mousePos)
{	
	bool left = mousePos.x - (va.getBounds().left + GetPosition().x) > 0;
	bool right = mousePos.x - (va.getBounds().width + GetPosition().x) < 0;
	bool top = mousePos.y - (va.getBounds().top + GetPosition().y) > 0;
	bool height = mousePos.y - (va.getBounds().height + GetPosition().y) < 0;

	return left && right && top && height;
}
