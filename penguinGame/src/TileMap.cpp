#include "../include/TileMap.h"

#include <fstream>
#include <sstream>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::getline;

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated){
    Load(file);
    this->tileSet = tileSet;    
}

void TileMap::Load(string file){
    ifstream inputOfFile(file);

    if (!inputOfFile.is_open()) {
        cout << "Erro, was not possible to open the file";
        return;
    }

    string line;
    while(getline(inputOfFile, line)){
        istringstream stream(line);
        int number;

        while(stream >> number){
            TileMatrix.emplace_back((number-1));

            if(stream.peek() == ','){
                stream.ignore();
            }
        }

    }
    inputOfFile.close();

    mapWidth = TileMatrix.front() + 1;
    TileMatrix.erase(TileMatrix.begin());

    mapHeight = TileMatrix.front() + 1;
    TileMatrix.erase(TileMatrix.begin());

    mapDepth = TileMatrix.front() + 1;
    TileMatrix.erase(TileMatrix.begin());
        
}

void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet =  tileSet;
}

int &TileMap::At(int x, int y, int z){
   int index = (z*mapWidth*mapHeight) + (y*mapWidth) + x;
   return TileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    
    for(int i = 0; i < mapWidth; i++){
        for(int j = 0; j < mapHeight; j++){
            
            int tileIndex = At(i, j, layer);
            int columnSize = tileSet->GetTileWidth();
            int rowSize = tileSet->GetTileHeight();
            tileSet->RenderTile(tileIndex, i * columnSize, j * rowSize);
        }
    }    
}

void TileMap::Render(){
    for(int i = 0; i < mapDepth; i++){
        RenderLayer(i, 0, 0);
    }
}

int TileMap::GetWidth(){
	return mapWidth;
}

int TileMap::GetHeight(){
	return mapHeight;
}

int TileMap::GetDepth(){
	return mapDepth;
}


void TileMap::Update(float dt){

}

bool TileMap::Is(string type){
    return (type == "TileMap") ? true : false;
}