

#include "TileContainer.h"

TileContainer::TileContainer(int numTiles, const Env &env) : numTiles(numTiles), environment(env), pos({}) {

}

int TileContainer::getNumTiles() const {
    return numTiles;
}

// Sets position and environment for which any subsequent extract.* method call will
// generate tiles for
void TileContainer::setExtractionPosition(const sf::Vector2f &position) {
    this->pos = position;
}


