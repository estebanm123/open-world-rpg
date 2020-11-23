

#include "EnvBorderData.h"

#include <utility>

EnvBorderData::EnvBorderData(std::shared_ptr<Env> primary, std::shared_ptr<Env> secondary) : primaryEnv(
        std::move(primary)),
                                                                                             secondaryEnv(std::move(
                                                                                                     secondary)) {
}