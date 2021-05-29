

#include "BeastInitializer.h"
#include "../NPC AI/NpcAi.h"
#include "../../../../../Util/Random/GlobalRand.h"

std::unique_ptr<Beast> BeastInitializer::initialize(BeastInitializer::Position pos) {
    auto activities = generateActivities(pos);
    auto ai = NpcAi<Beast>{std::move(activities)};

    auto hitbox = generateHitbox(pos);

    auto animPlayer = generateAnimPlayer(pos);
    auto sprite = generateSprite(pos, std::move(animPlayer));

    auto beast = std::make_unique<Beast>(std::move(hitbox), std::move(ai), std::move(sprite), getSpeed());
    auto surfaceEffectGenerator = generateSurfaceEffectGenerator(sf::Vector2f());
    beast->setSurfaceEffectGenerator(std::move(surfaceEffectGenerator));
    return beast;
}

std::unique_ptr<SurfaceEffectGenerator> BeastInitializer::generateSurfaceEffectGenerator(sf::Vector2f pos) {
    return nullptr;
}
