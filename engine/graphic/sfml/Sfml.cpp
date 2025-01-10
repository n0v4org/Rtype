/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SFML DisplayModule
*/

#include <iostream>
#include <string>

#include "Sfml.hpp"
#ifdef _MSC_VER
  #include <windows.h>
#endif

namespace zef {
  namespace graph {

    void Sfml::initialize(std::string assetFolderPath, std::string windowName) {
      _window.create(sf::VideoMode(_windowSize.first, _windowSize.second),
                     windowName.c_str());
      if (!_window.isOpen()) {
        throw WindowCreationException();
      }
      _window.setFramerateLimit(60);
      sf::View view({0, 0}, {1920, 1080});
      sf::View HUD({0, 0}, {1920, 1080});
      //    view.setCenter(0, 0);
      //    HUD.setCenter(0,0);
      _views["Default"] = view;
      _views["HUD"]     = HUD;

      _window.setView(view);
      loadAssets(assetFolderPath);
    }

    void Sfml::refresh() {
      _window.setView(_views["Default"]);
      //    _window.draw(_views["Default"]);
      _window.setView(_views["HUD"]);
      //    _window.draw(_views["HUD"]);
      _window.display();
    }

    void Sfml::clear() {
      _window.clear();
    }

    void Sfml::stop() {
      _window.close();
    }

    bool Sfml::isOpen() {
      return _window.isOpen();
    }

    Sfml::~Sfml() {
    }

    void Sfml::storeAssetsPNG(std::string assetPath) {
      sf::Texture texture;
      sf::Sprite sprite;
      std::string assetName =
          assetPath.substr(assetPath.find_last_of("/\\") + 1);
      assetName = assetName.substr(0, assetName.size() - 4);
      if (!texture.loadFromFile(assetPath.c_str())) {
        throw AssetLoadException();
      }
      std::cout << "Loading texture: " << assetName << std::endl;
      _sprites[assetName.c_str()] = {sprite, texture};
    }

    void Sfml::storeAssetsWAV(std::string assetPath) {
      sf::SoundBuffer soundbuffer;
      sf::Sound sound;
      std::string assetName =
          assetPath.substr(assetPath.find_last_of("/\\") + 1);
      assetName = assetName.substr(0, assetName.size() - 4);

      if (!soundbuffer.loadFromFile(assetPath.c_str())) {
        throw AssetLoadException();
      }
      sound.setBuffer(soundbuffer);
      sound.setVolume(50);

      _sounds[assetName.c_str()] = {sound, soundbuffer};
    }

    void Sfml::storeAssetsTTF(std::string assetPath) {
      sf::Font font;
      std::string assetName =
          assetPath.substr(assetPath.find_last_of("/\\") + 1);
      assetName = assetName.substr(0, assetName.size() - 4);

      if (!font.loadFromFile(assetPath.c_str())) {
        throw AssetLoadException();
      }
      std::cout << "Loading fonts: " << assetName << std::endl;
      _fonts[assetName.c_str()] = font;
    }

    void Sfml::storeAssetsSHAD(std::string assetPath) {
      std::string loadName = assetPath.substr(0, assetPath.size() - 4);
      std::string assetName =
          assetPath.substr(assetPath.find_last_of("/\\") + 1);
      assetName    = assetName.substr(0, assetName.size() - 5);
      auto& shader = _shaders[assetName];
      loadName     = loadName + "vert";

      if (!shader.loadFromFile(loadName.c_str(), sf::Shader::Vertex)) {
        throw AssetLoadException();
      }
      loadName = loadName.substr(0, loadName.size() - 4);
      loadName = loadName + "frag";
      if (!shader.loadFromFile(loadName.c_str(), sf::Shader::Fragment)) {
        throw AssetLoadException();
      }

      std::cout << "Loading shader: " << assetName << std::endl;
    }

    sf::Color Sfml::colorBlindness(RGBA mask) {
      std::string cb         = "ColorBlindness";
      std::string D          = "D";
      std::string P          = "P";
      std::string T          = "T";
      std::string colorBlind = _settings.find(cb)->second;
      RGBA colorBlindMask{1, 1, 1, 1};
      if (colorBlind == "None") {
        colorBlindMask = {1, 1, 1, 1};
      }
      if (colorBlind == D) {
        colorBlindMask = {1, 0.2, 1, 1};
      }
      if (colorBlind == P) {
        colorBlindMask = {0.2, 1, 1, 1};
      }
      if (colorBlind == T) {
        colorBlindMask = {1, 1, 0.2, 1};
      }
      if (colorBlind == "GreyScale") {
        colorBlindMask = {0.2, 0.2, 0.2, 1};
      }

      sf::Color color(255 * mask.R * colorBlindMask.R,
                      255 * mask.G * colorBlindMask.G,
                      255 * mask.B * colorBlindMask.B, 255 * mask.A);
      return color;
    }

    void Sfml::drawShaders(sf::Sprite sprite) {
      std::string cb = "ColorBlindness";
      if (_settings.find(cb) != _settings.end()) {
        _window.draw(sprite, &_shaders[_settings[cb]]);
      } else {
        _window.draw(sprite);
      }
    }

    void Sfml::drawSprite(std::string animationName, std::size_t currentFrame,
                          int posX, int posY, float scaleX, float scaleY,
                          float rotation, RGBA mask) {
      const zef::graph::Animation_t anim = _animations.at(animationName);

      _sprites.at(anim.SpriteSheet)
          .first.setTexture(_sprites.at(anim.SpriteSheet).second);
      _sprites.at(anim.SpriteSheet)
          .first.setTextureRect(
              sf::IntRect(anim.Size.first * currentFrame + anim.StartPos.first,
                          anim.StartPos.second * anim.Size.second,
                          anim.Size.first, anim.Size.second));
      _sprites.at(anim.SpriteSheet)
          .first.setColor(sf::Color(255 * mask.R, 255 * mask.G, 255 * mask.B,
                                    255 * mask.A));
      //    sprite.setColor(colorBlindness(mask));
      _sprites.at(anim.SpriteSheet).first.setRotation(rotation);

      _sprites.at(anim.SpriteSheet)
          .first.setOrigin(anim.Size.first / 2, anim.Size.second / 2);
      _sprites.at(anim.SpriteSheet).first.setPosition(posX, posY);
      _sprites.at(anim.SpriteSheet).first.setScale(scaleX, scaleY);

      _window.setView(_views["Default"]);
      drawShaders(_sprites.at(anim.SpriteSheet).first);
      //    if (_shaders.find("tritanopia") != _shaders.end()) {
      //      _shaders["tritanopia"].setUniform("texture",
      //      sf::Shader::CurrentTexture); _window.draw(sprite,
      //      &_shaders["tritanopia"]);
      //    } else {
      //      _window.draw(sprite);
      //    }
    }

    void Sfml::drawSpriteHUD(std::string animationName,
                             std::size_t currentFrame, int posX, int posY,
                             float scaleX, float scaleY, float rotation,
                             RGBA mask) {
      const zef::graph::Animation_t anim = _animations.at(animationName);

      _sprites.at(anim.SpriteSheet)
          .first.setTexture(_sprites.at(anim.SpriteSheet).second);
      _sprites.at(anim.SpriteSheet)
          .first.setTextureRect(
              sf::IntRect(anim.Size.first * currentFrame + anim.StartPos.first,
                          anim.StartPos.second * anim.Size.second,
                          anim.Size.first, anim.Size.second));
      _sprites.at(anim.SpriteSheet)
          .first.setColor(sf::Color(255 * mask.R, 255 * mask.G, 255 * mask.B,
                                    255 * mask.A));
      //    sprite.setColor(colorBlindness(mask));
      _sprites.at(anim.SpriteSheet).first.setRotation(rotation);

      _sprites.at(anim.SpriteSheet)
          .first.setOrigin(anim.Size.first / 2, anim.Size.second / 2);
      _sprites.at(anim.SpriteSheet).first.setPosition(posX, posY);
      _sprites.at(anim.SpriteSheet).first.setScale(scaleX, scaleY);

      _window.setView(_views["HUD"]);
      drawShaders(_sprites.at(anim.SpriteSheet).first);
      //    _window.draw(sprite);
      //    if (_shaders.find("tritanopia") != _shaders.end()) {
      //      _shaders["tritanopia"].setUniform("texture",
      //      sf::Shader::CurrentTexture); _window.draw(sprite,
      //      &_shaders["tritanopia"]);
      //    } else {
      //      _window.draw(sprite);
      //    }
    }

    void Sfml::drawText(std::string textString, std::string fontName,
                        std::size_t fontSize, int posX, int posY, float scaleX,
                        float scaleY, float rotation, RGBA mask) {
      sf::Font font = _fonts.find(fontName)->second;
      sf::Text text(textString, font, fontSize);
      sf::Color color(255 * mask.R, 255 * mask.G, 255 * mask.B, 255 * mask.A);

      sf::FloatRect textRect = text.getLocalBounds();
      text.setOrigin(textRect.left + textRect.width / 2,
                     textRect.top + textRect.height / 2);
      text.setPosition(posX, posY);
      text.setScale(scaleX, scaleY);
      text.setFillColor(color);
      text.setRotation(rotation);

      _window.setView(_views["Default"]);
      _window.draw(text);
    }

    void Sfml::drawTextHUD(std::string textString, std::string fontName,
                           std::size_t fontSize, int posX, int posY,
                           float scaleX, float scaleY, float rotation,
                           RGBA mask) {
      sf::Font font = _fonts.find(fontName)->second;
      sf::Text text(textString, font, fontSize);
      sf::Color color(255 * mask.R, 255 * mask.G, 255 * mask.B, 255 * mask.A);

      sf::FloatRect textRect = text.getLocalBounds();
      text.setOrigin(textRect.left + textRect.width / 2,
                     textRect.top + textRect.height / 2);
      text.setPosition(posX, posY);
      text.setScale(scaleX, scaleY);
      text.setFillColor(color);
      text.setRotation(rotation);

      _window.setView(_views["HUD"]);
      _window.draw(text);
    }

    void Sfml::playSound(std::string soundName, int volume) {
      _sounds.find(soundName)->second.first.setBuffer(
          _sounds.find(soundName)->second.second);
      _sounds.find(soundName)->second.first.setVolume(volume);
      std::cout << soundName << std::endl;
      _sounds.find(soundName)->second.first.play();
    }

    void Sfml::saveAnimation(std::string animationName,
                             std::string spriteSheetName,
                             std::size_t startTileX, std::size_t startTileY,
                             std::size_t tileSizeX, std::size_t tileSizeY) {
      Animation_t animation{
          spriteSheetName, {startTileX, startTileY}, {tileSizeX, tileSizeY}};

      _animations[animationName.c_str()] = animation;
    }

    void Sfml::moveCamera(int X, int Y, float Z) {
      if (!_window.getView().getViewport().width) {
        sf::View defaultView = _window.getDefaultView();
        _views["Default"]    = defaultView;
      }

      _views["Default"].setCenter(_views["Default"].getCenter().x + X,
                                  _views["Default"].getCenter().y + Y);
      _views["Default"].zoom(Z);
      _window.setView(_views["Default"]);
    }

    void Sfml::setCamera(int X, int Y, int Z) {
      if (!_window.getView().getViewport().width) {
        sf::View defaultView = _window.getDefaultView();
        _views["Default"]    = defaultView;
      }

      _views["Default"].move(X, Y);
      _views["Default"].zoom(1.0f + Z / 100.0f);
      _window.setView(_views["Default"]);
    }

    void Sfml::updateUserInputs(utils::UserInputs& ui) {
      sf::Event evt;
      while (_window.pollEvent(evt)) {
        if (evt.type == evt.KeyPressed) {
          if (ui.keyboard._key_map[static_cast<utils::Keys>(evt.key.code)] ==
              false)
            ui.keyboard._pressed.push_back(
                static_cast<utils::Keys>(evt.key.code));
          ui.keyboard._key_map[static_cast<utils::Keys>(evt.key.code)] = true;
        }
        if (evt.type == evt.KeyReleased) {
          ui.keyboard._key_map[static_cast<utils::Keys>(evt.key.code)] = false;
          ui.keyboard._released.push_back(
              static_cast<utils::Keys>(evt.key.code));
        }
        if (evt.type == evt.MouseButtonPressed) {
          if (ui.mouse._mb_map[static_cast<utils::MouseButtons>(
                  evt.mouseButton.button)] == false)
            ui.mouse._pressed.push_back(
                static_cast<utils::MouseButtons>(evt.mouseButton.button));
          ui.mouse._mb_map[static_cast<utils::MouseButtons>(
              evt.mouseButton.button)] = true;
        }
        if (evt.type == evt.MouseButtonReleased) {
          ui.mouse._mb_map[static_cast<utils::MouseButtons>(
              evt.mouseButton.button)] = false;
          ui.mouse._released.push_back(
              static_cast<utils::MouseButtons>(evt.mouseButton.button));
        }

        sf::Vector2i mousePosWindow = sf::Mouse::getPosition(_window);
        sf::Vector2f mousePosInView = _window.mapPixelToCoords(mousePosWindow);

        ui.mouse.x = mousePosInView.x;
        ui.mouse.y = mousePosInView.y;
      }
    }

    UserInput Sfml::getEvent() {
      UserInput userInput;

      sf::Event event;
      while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          userInput.Close = true;
        if (event.type == sf::Event::KeyPressed) {
          if (event.text.unicode == 3) {
            userInput.Pressed_D = true;
          }
          if (event.text.unicode == 8) {
            userInput.Pressed_I = true;
          }
          if (event.text.unicode == 9) {
            userInput.Pressed_J = true;
          }
          if (event.text.unicode == 10) {
            userInput.Pressed_K = true;
          }
          if (event.text.unicode == 11) {
            userInput.Pressed_L = true;
          }
          if (event.text.unicode == 12) {
            userInput.Pressed_M = true;
          }
          if (event.text.unicode == 15) {
            userInput.Pressed_P = true;
          }
          if (event.text.unicode == 16) {
            userInput.Pressed_Q = true;
          }
          if (event.text.unicode == 18) {
            userInput.Pressed_S = true;
          }
          if (event.text.unicode == 25) {
            userInput.Pressed_Z = true;
          }
        }
      }
      return userInput;
    }

  }  // namespace graph
}  // namespace zef



extern "C" 
#ifdef _MSC_VER
  __declspec(dllexport)
#endif
zef::graph::IDisplayModule* entryPoint() {
  return new zef::graph::Sfml;
}
