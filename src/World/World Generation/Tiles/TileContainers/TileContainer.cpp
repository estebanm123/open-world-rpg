

#include "TileContainer.h"

#include "../../Environments/CompleteEnv.h"

TileContainer::TileContainer(int numTiles) : numTiles(numTiles) {}

int TileContainer::getNumTiles() const { return numTiles; }
