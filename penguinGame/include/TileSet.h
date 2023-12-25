#include <iostream>
#include <Sprite.h>

#pragma once

using std::string;

class TileSet{

    public:

        TileSet(int tileWidth, int tileHeight, string file);
        void RenderTile(unsigned index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();

    private:

        // @TODO set the right gameObject associated to the tileSet
	    GameObject* gameObjectToTile = new GameObject();
	    Sprite* tileSet = new Sprite(*gameObjectToTile);
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;
};
