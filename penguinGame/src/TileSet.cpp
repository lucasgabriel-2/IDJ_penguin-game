#include "../include/TileSet.h"

using std::string;
using std::cout;

TileSet::TileSet(int tileWidth, int tileHeight, string file){
	
    this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	tileSet->Open(file);

	if(tileSet->IsOpen()){
		columns = tileSet->GetWidth()/tileWidth;
		rows = tileSet->GetHeight()/tileHeight;
	}else{
		cout << "Error, was not possible to open this TileSetImage";
	}
}

void TileSet::RenderTile(unsigned index, float x ,float y){
	
	unsigned numberOfTiles = columns*rows;

	// Find the row and column (in the matrix) with the linear Indexed TileSet number(index)
	unsigned tileRow = index/columns;
	unsigned tileColumn = index%columns;

	unsigned setClipX = tileColumn * tileWidth ;
	unsigned setClipY = tileRow * tileHeight;
	if((index >= 0) && (index <= (numberOfTiles-1))){
		tileSet->SetClip(setClipX, setClipY, tileWidth, tileHeight);
		tileSet->Render(x,y);
	}else{
		// @TODO fix:
		// cout << "Error, was not possible to renderTitle, index out of bounds\n";
	}
	
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

int TileSet::GetTileHeight(){
	return tileHeight;
}