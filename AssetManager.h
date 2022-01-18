#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>


class AssetManager
{
    private:
        std::map<std::string, std::unique_ptr<sf::Texture>> textures;
        std::map<std::string, std::unique_ptr<sf::Font>> fonts;

    public:
        AssetManager();
        ~AssetManager();

        void AddTexture(std::string name, const std::string& filePath, bool wantRepeated = false);
        void AddFont(std::string name, const std::string& filePath);

        const sf::Texture& GetTexture(std::string name) const;
        const sf::Font& GetFont(std::string name) const;
};
