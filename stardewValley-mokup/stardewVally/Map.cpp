#include "stdafx.h"
#include "Map.h"

std::ostream& operator <<(std::ostream& ost, sf::Vector2f cellTextCoord[4]) {
    ost << cellTextCoord[0].x << ", " << cellTextCoord[0].y << ", " << cellTextCoord[1].x << ", " << cellTextCoord[1].y << ", " << cellTextCoord[2].x << ", " << cellTextCoord[2].y << ", " << cellTextCoord[3].x << ", " << cellTextCoord[3].y << ", ";

    return ost;
}

void Map::Reset(int size)
{
    cell.insert({ 0 , std::vector<CellData>() });
    cell.insert({ 1 , std::vector<CellData>() });

    cell[0].resize(size);
    cell[1].resize(size);
}

int Map::GetCellIndex(int idx , int layer)
{
    return cell[layer][idx].idx;
}
int Map::GetCellIndex(const sf::Vector2f& pos, int layer)
{
    int xIndex = (int)(pos.x / 16);
    int yIndex = (int)(pos.y / 16);

    int idx = xIndex + (yIndex * count.x);

    return idx;
}

CellData& Map::GetCell(int idx, int layer)
{
    return cell[layer][idx];
}
CellData& Map::GetCell(const sf::Vector2f& pos, int layer)
{
    int idx = GetCellIndex(pos, layer);
    return cell[layer][idx];
}

CellData Map::GetTextureCell(const int idx, const int layer)
{
    CellData textureCellData;
    textureCellData.cellTextCoord[0] = { idx % count.x * 16.f, idx / count.x * 16.f };
    textureCellData.cellTextCoord[1] = { (idx % count.x + 1) * 16.f, idx / count.x * 16.f };
    textureCellData.cellTextCoord[2] = { (idx % count.x + 1) * 16.f, (idx / count.x + 1) * 16.f };
    textureCellData.cellTextCoord[3] = { idx % count.x * 16.f, (idx / count.x + 1) * 16.f };

    std::cout << textureCellData.cellTextCoord << std::endl;
    textureCellData.idx = idx;

    return textureCellData;
}

void Map::SetCellData(int idx, int layer, const CellData* cellData)
{
    cell[layer][idx].cellTextCoord[0] = cellData->cellTextCoord[0];
    cell[layer][idx].cellTextCoord[1] = cellData->cellTextCoord[1];
    cell[layer][idx].cellTextCoord[2] = cellData->cellTextCoord[2];
    cell[layer][idx].cellTextCoord[3] = cellData->cellTextCoord[3];
}

void Map::LoadCollider(const std::string path)
{
    std::ifstream file(path);
    
    if (!file.good()) {
        std::cout << "FAIL TO LOAD FILE " << path << std::endl;
        return;
    }

    rapidcsv::Document document(path);

    if (document.GetRowCount() == 0) return;
       
    
    for (int i = 0; i < document.GetRowCount(); i++) {
        auto cellData = document.GetCell<std::string>(0, i);

        //0 1 size , 2 3 pos
        auto split = Utils::Split(cellData, ',');
        sf::Vector2f size = { std::stof(split[0]) , std::stof(split[1]) };
        sf::Vector2f pos = { std::stof(split[2]) - 300.f, std::stof(split[3]) - 300.f };

        colliders.push_back(new sf::RectangleShape());
        colliders[colliders.size() - 1]->setSize(size);
        colliders[colliders.size() - 1]->setPosition(pos);
        colliders[colliders.size() - 1]->setFillColor(sf::Color::Transparent);
        colliders[colliders.size() - 1]->setOutlineColor(sf::Color::Green);
        colliders[colliders.size() - 1]->setOutlineThickness(1.f);
    }
}


void Map::Load(const std::string path , int layer)
{
    std::ifstream file(path);
    std::vector<CellData> data;

    if (!file.good()) {
        std::cout << "FAIL TO LOAD FILE " << path << std::endl;
        return ;
    }

    rapidcsv::Document document(path);
    if (document.GetRowCount() == 0) return ;

    Reset(document.GetCell<int>(1, 0));
    textures[layer] = document.GetCell<std::string>(0, 0);

    int quadIndex = 0;
    int k = 0;
    
    count.x = document.GetRow<int>(1).size();
    count.y = document.GetRowCount() - 1;

    for (int i = 1; i < document.GetRowCount(); i++) {
        auto row = document.GetRow<int>(i);
        
        for (int j = 0; j < row.size(); j++) {
            CellData cellData;
            if (row[j] == -1) {
                cellData.cellTextCoord[0] = { 0, 0 };
                cellData.cellTextCoord[1] = { 0, 0 };
                cellData.cellTextCoord[2] = { 0, 0 };
                cellData.cellTextCoord[3] = { 0, 0 };
            }
            else {
                cellData.cellTextCoord[0] = { row[j] % row.size() * 16.f, row[j] / row.size() * 16.f };
                cellData.cellTextCoord[1] = { (row[j] % row.size() + 1) * 16.f, row[j] / row.size() * 16.f };
                cellData.cellTextCoord[2] = { (row[j] % row.size() + 1) * 16.f, (row[j] / row.size() + 1) * 16.f };
                cellData.cellTextCoord[3] = { row[j] % row.size() * 16.f, (row[j] / row.size() + 1) * 16.f };
            }
            cellData.cellPosition[0] = { j * 16.f , (i - 1) * 16.f};
            cellData.cellPosition[1] = { (j + 1) * 16.f , (i - 1) * 16.f };
            cellData.cellPosition[2] = { (j + 1) * 16.f , (i) * 16.f };
            cellData.cellPosition[3] = { j * 16.f , (i) * 16.f };

            cellData.idx = row[j];
            cell[layer][k++] = cellData;
        }
    }
}

void Map::LoadTrigger(const std::string path)
{
    std::ifstream file(path);

    if (!file.good()) {
        std::cout << "FAIL TO LOAD FILE " << path << std::endl;
        return;
    }

    rapidcsv::Document document(path);

    if (document.GetRowCount() == 0) return;


    for (int i = 0; i < document.GetRowCount(); i++) {
        auto cellData = document.GetCell<std::string>(0, i);

        //0 1 size , 2 3 pos
        auto split = Utils::Split(cellData, ',');
        sf::Vector2f size = { std::stof(split[0]) , std::stof(split[1]) };
        sf::Vector2f pos = { std::stof(split[2]) - 300.f, std::stof(split[3]) - 300.f };
        int type = std::stoi(split[4]);

        triggers.push_back(new Trigger());
        triggers[triggers.size() - 1]->Reset();
        triggers[triggers.size() - 1]->SetSize(size);
        triggers[triggers.size() - 1]->SetPosition(pos);
        triggers[triggers.size() - 1]->SetType((TriggerType)type);
    }
}

void Map::Load(const std::string path)
{
    Load(path + ".csv", 0);
    Load(path+"forGround.csv", 1);
    LoadCollider(path +"collider.csv");
    LoadTrigger(path + "trigger.csv");
}

void Map::Save(const std::string path, std::vector<Trigger*>& triggerData) {
    rapidcsv::Document doc;

    for (int i = 0; i < triggerData.size(); i++) {
        sf::Vector2f size = triggerData[i]->GetSize();
        sf::Vector2f pos = triggerData[i]->GetPosition();
        int type = (int)triggerData[i]->GetType();

        
        std::string data = std::to_string(size.x) + "," + std::to_string(size.y) + "," + std::to_string(pos.x) + "," + std::to_string(pos.y) + "," + std::to_string(type);

        std::cout << data << std::endl;
        doc.SetCell<std::string>(0, i, data);
    }

    std::ifstream file(path);
    if (file.good()) {
        std::cout << "REMOVE FILE" << std::endl;
        remove(path.c_str());
    }
    std::cout << "CREATE FILE" << std::endl;
    doc.Save(path);
}

void Map::Save(const std::string path, std::string texId, std::vector<CellData>& cellData, sf::Vector2i count)
{
    rapidcsv::Document doc;

    doc.SetCell<std::string>(0, 0, texId);
    doc.SetCell<int>(1, 0, cellData.size());

    for (int i = 0; i < count.y; i++) {
        std::vector<int> idx;
        int quadIdx = i * count.x;

        for (int j = 0; j < count.x; j++) {
            idx.push_back(cellData[quadIdx + j].idx);
        }
        doc.SetRow<int>(i + 1, idx);
    }

    std::ifstream file(path);
    if (file.good()) {
        std::cout << "REMOVE FILE" << std::endl;
        remove(path.c_str());
    }
    std::cout << "CREATE FILE" << std::endl;
    doc.Save(path);
}

void Map::Save(const std::string path, std::vector<sf::RectangleShape*>& colliderData)
{
    rapidcsv::Document doc;
    
    for (int i = 0; i < colliderData.size(); i++) {
        sf::Vector2f bounds = colliderData[i]->getSize();
        sf::Vector2f pos = colliderData[i]->getPosition();
        doc.SetCell<std::string>(0, i, std::to_string(bounds.x) + "," + std::to_string(bounds.y) + "," + std::to_string(pos.x) + "," + std::to_string(pos.y));
    }

    std::ifstream file(path);
    if (file.good()) {
        std::cout << "REMOVE FILE" << std::endl;
        remove(path.c_str());
    }
    std::cout << "CREATE FILE" << std::endl;
    doc.Save(path);
}

std::vector<CellData>& Map::GetCellDatas(int layer)
{
    return cell[layer];
}

void Map::Release()
{
    for (auto col : colliders) {
        delete col;
    }
    
    colliders.clear();
}