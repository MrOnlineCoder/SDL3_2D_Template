#include <Resources/AssetsManager.hpp>

#include <Common/Logger.hpp>

const std::string ASSETS_ROOT = "assets/";

AssetsManager::AssetsManager()
{
    m_textures.reserve(32);
    m_soundBuffers.reserve(32);
}

AssetsManager::~AssetsManager()
{
    for (auto &texture : m_textures)
    {
        delete texture.second;
    }

    for (auto &soundBuffer : m_soundBuffers)
    {
        delete soundBuffer.second;
    }
}

void AssetsManager::loadMainFont(const std::string &relativePath)
{
    m_mainFont.loadFromFile(ASSETS_ROOT + relativePath);

    LOG_INFO("Loaded main font: %s", relativePath.c_str());
}

void AssetsManager::loadSound(const std::string &name, const std::string &relativePath)
{
    SoundBuffer *soundBuffer = new SoundBuffer();

    soundBuffer->loadFromFile(ASSETS_ROOT + relativePath);

    m_soundBuffers[name] = soundBuffer;

    LOG_INFO("Loaded sound: %s", name.c_str());
}

void AssetsManager::loadTexture(const std::string &name, const std::string &relativePath)
{
    Texture *tex = new Texture();

    if (tex->loadFromFile(ASSETS_ROOT + relativePath))
    {
        LOG_INFO("Loaded texture: %s", name.c_str());
        m_textures[name] = tex;
    }
    else
    {
        LOG_ERROR("Failed to load texture %s from '%s'", name.c_str(), relativePath.c_str());
        delete tex;
    }
}

void AssetsManager::playSound(const std::string &name, int count)
{
    auto soundBuffer = m_soundBuffers.at(name);

    if (soundBuffer)
    {
        soundBuffer->play(count - 1);
    }
}

void AssetsManager::playMusic(const std::string &name)
{
    m_music.openFromFile(ASSETS_ROOT + "music/" + name + ".mp3");
    m_music.play();
}

void AssetsManager::pauseMusic()
{
    m_music.pause();
}

void AssetsManager::stopMusic()
{
    m_music.stop();
}