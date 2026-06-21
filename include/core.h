#pragma once
class Body {
    public:
        Vector2 position;
        Vector2 velocity;
        void update_position(float dt);
};
