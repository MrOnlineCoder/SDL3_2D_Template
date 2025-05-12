#include <Render/AnimatedSprite.hpp>

#include <Common/Debug.hpp>

AnimatedSprite::AnimatedSprite()
    : m_animation(nullptr), m_isPaused(false), m_currentFrame(0), m_elapsedTime(0), m_frameTime(0.1f)
{
}

void AnimatedSprite::setAnimation(const Animation &animation)
{
    m_animation = &animation;
    ASSERT(m_animation->getTexture() != nullptr);
    m_sprite.setTexture(*m_animation->getTexture());
    m_sprite.setTextureRect(m_animation->getFrames()[0]);
}

void AnimatedSprite::play()
{
    m_isPaused = false;
}

void AnimatedSprite::pause()
{
    m_isPaused = true;
}

bool AnimatedSprite::isPaused() const
{
    return m_isPaused;
}

void AnimatedSprite::update(float deltaTime)
{
    if (m_isPaused)
        return;

    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_frameTime)
    {
        m_elapsedTime = 0;
        m_currentFrame = (m_currentFrame + 1) % m_animation->getFrames().size();
        m_sprite.setTextureRect(m_animation->getFrames()[m_currentFrame]);
    }
}

void AnimatedSprite::render()
{
    if (!m_animation)
        return;

    m_sprite.render();
}

void AnimatedSprite::setPosition(const Vector2f &pos)
{
    m_sprite.setPosition(pos);
}

void AnimatedSprite::setFrameTime(float seconds)
{
    m_frameTime = seconds;
}