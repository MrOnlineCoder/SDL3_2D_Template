#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <Resources/Texture.hpp>
#include <Common/Rect.hpp>
#include <Render/Sprite.hpp>

#include <vector>

class Animation
{
public:
    Animation() : m_texture(nullptr)
    {
        m_frames.reserve(8);
    }

    void setSpriteSheet(
        const Texture &texture)
    {
        m_texture = &texture;
    }

    void addFrame(
        const IntRect &frame)
    {
        m_frames.push_back(frame);
    }

    const std::vector<IntRect> &getFrames() const
    {
        return m_frames;
    }

    const Texture *getTexture() const
    {
        return m_texture;
    }

private:
    const Texture *m_texture;
    std::vector<IntRect> m_frames;
};

class AnimatedSprite
{
public:
    AnimatedSprite();

    void setAnimation(const Animation &animation);

    void play();
    void pause();
    bool isPaused() const;

    void update(float deltaTime);
    void render();

    void setPosition(const Vector2f &pos);
    void setFrameTime(float seconds);

    const Sprite &getSprite() const { return m_sprite; }

private:
    bool m_isPaused;
    Sprite m_sprite;
    const Animation *m_animation;
    unsigned int m_currentFrame;
    float m_elapsedTime;
    float m_frameTime;
};

#endif