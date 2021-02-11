

#include "../../Environments/CompleteEnv.h"
#include "TileContainer.h"

TileContainer::TileContainer(int numTiles) : numTiles(numTiles) {

}

int TileContainer::getNumTiles() const {
    return numTiles;
}

