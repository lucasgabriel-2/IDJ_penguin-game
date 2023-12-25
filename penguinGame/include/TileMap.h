#include <iostream>
#include <TileSet.h>

#pragma once

class TileMap : public Component{

    public:

        TileMap(GameObject& associated, string file, TileSet* tileSet);
        void Load(string file);
        void SetTileSet(TileSet* TileSet);
        int& At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();
        void Update(float dt);
        bool Is(string type);

    private:

        vector<int> TileMatrix;
        TileSet* tileSet; 
        int mapWidth;
        int mapHeight;
        int mapDepth;

};
