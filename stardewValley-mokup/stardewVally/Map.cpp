#include "stdafx.h"
#include "Map.h"

void Map::Reset(int size)
{
    cell.clear();

    cell.insert({ 0 , std::vector<CellData>() });
    cell.insert({ 1 , std::vector<CellData>() });

    cell[0].resize(size);
    cell[1].resize(size);
}

//Idx 값에 맞춰서 행동 수행하면 될듯!
int Map::GetCellIndex(int idx , int layer)
{
    return cell[layer][idx].idx;
}

std::vector<sf::RectangleShape*>& Map::Load(const std::string path)
{
    std::ifstream file(path);
    
    if (!file.good()) {
        std::cout << "FAIL TO LOAD FILE " << path << std::endl;
        return colliders;
    }

    rapidcsv::Document document(path);

    if (document.GetColumnCount() == 0) return colliders;
       
    
    for (int i = 0; i < document.GetColumnCount(); i++) {
        auto cellData = document.GetCell<std::string>(0, i);

        //0 1 size , 2 3 pos
        auto split = Utils::Split(cellData, ',');
        sf::Vector2f size = { std::stof(split[0]) , std::stof(split[1]) };
        sf::Vector2f pos = { std::stof(split[2]) - 300.f, std::stof(split[3]) - 300.f };

        colliders.push_back(new sf::RectangleShape());
        colliders[colliders.size() - 1]->setSize(size);
        colliders[colliders.size() - 1]->setSize(pos);
        std::cout << "pos : " << pos.x << ", " << pos.y << std::endl;
    }
}

std::vector<CellData>& Map::Load(const std::string path , int layer)
{
    std::ifstream file(path);
    std::vector<CellData> data;

    if (!file.good()) {
        std::cout << "FAIL TO LOAD FILE " << path << std::endl;
        return data;
    }

    rapidcsv::Document document(path);
    if (document.GetRowCount() == 0) return data;

    Reset(document.GetCell<int>(1, 0));
    texId = document.GetCell<std::string>(0, 0);

    int quadIndex = 0;
    int k = 0;
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

            cell[layer][k++] = cellData;
        }
        
    }

    return cell[layer];
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

void Map::Release()
{
    for (auto col : colliders) {
        delete col;
    }
    
    colliders.clear();
}
