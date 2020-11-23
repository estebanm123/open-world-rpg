
#include <string>
#include <vector>
#include <memory>
#include "../../../Util/Random/Hash.h"
#include "../Tiles/TileContainer.h"
#include "NeighboredEnv.h"


class CompleteEnv : public NeighboredEnv, sf::NonCopyable, NonMoveable {
public:
    static inline std::string TILE_SHEET_PATH = "Levels/tiles";

    struct Config {
        Config() {};
        std::string spriteSheet = TILE_SHEET_PATH;
        int multiTileIndex = -1; // maybe refactor this out to only env - depends on if borderenvs can have multiple tiles
        bool isPriority = false;
    };

    explicit CompleteEnv(struct CompleteEnv::Config config = CompleteEnv::Config{}) noexcept;

    virtual std::shared_ptr<TileContainer> selectTileContainer(const sf::Vector2f & coords) const = 0;

    const std::string &getSpriteSheetPath() const;

    void setSingleTileContainers(TileContainer::TileContainers & singleTileContainers);

    bool isPriorityEnv() const;

    void togglePriority();
protected:
    const int multiTileIndex;
    TileContainer::TileContainers singleTileContainers;

private:
    bool isPriority;
    const std::string spriteSheet;
};






