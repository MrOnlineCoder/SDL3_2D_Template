#ifndef ASSETS_MANANGER_HPP
#define ASSETS_MANANGER_HPP

#include <Resources/Texture.hpp>
#include <Resources/Font.hpp>
#include <Resources/SoundBuffer.hpp>
#include <Resources/Music.hpp>

#include <unordered_map>
#include <string>

class AssetsManager
{
public:
    AssetsManager();
    ~AssetsManager();

    void loadMainFont(const std::string &relativePath);
    void loadSound(const std::string &name, const std::string &relativePath);
    void loadTexture(const std::string &name, const std::string &relativePath);

    void playSound(const std::string &name, int count = 1);

    void playMusic(const std::string &name);
    void pauseMusic();
    void stopMusic();

    const Font &getMainFont() const { return m_mainFont; }
    const Texture &getTexture(const std::string &name) const { return *m_textures.at(name); }
    const SoundBuffer &getSoundBuffer(const std::string &name) const { return *m_soundBuffers.at(name); }

private:
    std::unordered_map<std::string, Texture *> m_textures;
    std::unordered_map<std::string, SoundBuffer *> m_soundBuffers;
    Font m_mainFont;
    Music m_music;
};

#endif