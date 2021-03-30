#pragma once

class Observable;


class Observer {

public:
    enum NotifType {
        PLAYER_HIT,
        ENEMY_KILLED
    };

    virtual void update(const Observable &info, NotifType type) = 0;

    virtual ~Observer() = default;
};
