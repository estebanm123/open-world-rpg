#pragma once

class Subject;


class Observer {

public:
    enum NotifType {
        PLAYER_HIT,
        ENEMY_KILLED
    };

    virtual void update(const Subject &info, NotifType type) = 0;

    virtual ~Observer() = default;
};
