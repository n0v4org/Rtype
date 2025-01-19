/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SFML DisplayModule
*/


#ifdef _MSC_VER
  #include <windows.h>
#endif
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "Sfml.hpp"
#include "HPBar.hpp"
#define M_PI 3.14159265358979323846

namespace zef {
  namespace graph {

    void Sfml::initialize(std::string assetFolderPath, std::string windowName,
                          std::pair<int, int> windowSize) {
      _windowSize = windowSize;
      _window.create(sf::VideoMode(_windowSize.first, _windowSize.second),
                     windowName.c_str());
      if (!_window.isOpen()) {
        throw WindowCreationException();
      }
      _window.setFramerateLimit(60);
      sf::View view({0, 0}, {static_cast<float>(_windowSize.first),
                             static_cast<float>(_windowSize.second)});
      sf::View HUD({0, 0}, {static_cast<float>(_windowSize.first),
                            static_cast<float>(_windowSize.second)});
      //    view.setCenter(0, 0);
      //    HUD.setCenter(0,0);
      _views["Default"] = view;
      _views["HUD"]     = HUD;

      _window.setView(view);
      loadAssets(assetFolderPath);
    }

    void Sfml::refresh() {
      drawParticleEmmiters();
      _window.display();
    }

    void Sfml::drawParticleEmmiters() {
      for (auto particleEmmiter : _particleEmmiters) {
        for (int i = 0; i < particleEmmiter.second.density; i++) {
          if (_particleEmmiters[particleEmmiter.first]
                  .particles[i]
                  .startupTime <= 0) {
            _particleEmmiters[particleEmmiter.first].particles[i].lifeTime -=
                rand() % 10;
          } else {
            _particleEmmiters[particleEmmiter.first].particles[i].startupTime -=
                rand() % 10;
          }

          if (_particleEmmiters[particleEmmiter.first].particles[i].lifeTime <=
              0) {
            _particleEmmiters[particleEmmiter.first].particles[i].posX = 0;
            _particleEmmiters[particleEmmiter.first].particles[i].posY = 0;
            _particleEmmiters[particleEmmiter.first].particles[i].lifeTime =
                _particleEmmiters[particleEmmiter.first].lifeTime;
            _particleEmmiters[particleEmmiter.first].particles[i].direction =
                static_cast<float>(
                    (rand() % _particleEmmiters[particleEmmiter.first]
                                  .rotationRange +
                     _particleEmmiters[particleEmmiter.first].rotationStart) *
                    (M_PI / 180.0));
            _particleEmmiters[particleEmmiter.first].particles[i].velocity =
                _particleEmmiters[particleEmmiter.first].velocity -
                (rand() % _particleEmmiters[particleEmmiter.first].velocity /
                 4);
            _particleEmmiters[particleEmmiter.first].particles[i].startupTime =
                _particleEmmiters[particleEmmiter.first].particles[i].lifeTime -
                (rand() % _particleEmmiters[particleEmmiter.first]
                              .particles[i]
                              .lifeTime);
          }

          if (_particleEmmiters[particleEmmiter.first]
                  .particles[i]
                  .startupTime <= 0) {
            _particleEmmiters[particleEmmiter.first].particles[i].posX +=
                _particleEmmiters[particleEmmiter.first].particles[i].velocity *
                cos(_particleEmmiters[particleEmmiter.first]
                        .particles[i]
                        .direction);
            _particleEmmiters[particleEmmiter.first].particles[i].posY +=
                _particleEmmiters[particleEmmiter.first].particles[i].velocity *
                sin(_particleEmmiters[particleEmmiter.first]
                        .particles[i]
                        .direction);

            drawSprite(
                _particleEmmiters[particleEmmiter.first].spriteSheet, 0,
                _particleEmmiters[particleEmmiter.first].posX +
                    _particleEmmiters[particleEmmiter.first].particles[i].posX,
                _particleEmmiters[particleEmmiter.first].posY +
                    _particleEmmiters[particleEmmiter.first].particles[i].posY,
                _particleEmmiters[particleEmmiter.first].scaleX,
                _particleEmmiters[particleEmmiter.first].scaleY,
                _particleEmmiters[particleEmmiter.first].particles[i].direction,
                {_particleEmmiters[particleEmmiter.first].mask.R,
                 _particleEmmiters[particleEmmiter.first].mask.G,
                 _particleEmmiters[particleEmmiter.first].mask.B,
                 _particleEmmiters[particleEmmiter.first].mask.A *
                     (static_cast<float>(
                          _particleEmmiters[particleEmmiter.first]
                              .particles[i]
                              .lifeTime) /
                      static_cast<float>(
                          _particleEmmiters[particleEmmiter.first].lifeTime))},
                _particleEmmiters[particleEmmiter.first].objectShaders,
                _particleEmmiters[particleEmmiter.first].addActive);
          }
          //        _sprites[particleEmmiter.second.spriteSheet].first.setPosition(_particleEmmiters[particleEmmiter.first].posX
          //        +
          //        _particleEmmiters[particleEmmiter.first].particles[i].posX,
          //        _particleEmmiters[particleEmmiter.first].posY +
          //        _particleEmmiters[particleEmmiter.first].particles[i].posY);
          //        _window.draw(_sprites[particleEmmiter.second.spriteSheet].first);
        }
      }
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
      sf::Text text("",font,1);
      std::cout << "Loading fonts: " << assetName << std::endl;

      _fonts[assetName.c_str()] = {font,text};
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

    void Sfml::drawShaders(sf::Sprite sprite,
                           std::vector<std::string>& objectShaders,
                           bool addActive) {
      std::vector<std::string> shaders = {
          _settings.find(std::string("ColorBlindness"))->second};
      for (auto& shader : objectShaders) {
        shaders.push_back(shader);
      }
      if (addActive) {
        for (auto& shader : _activeShaders) {
          shaders.push_back(shader);
        }
      }
      if (shaders.empty()) {
        _window.draw(sprite);
        return;
      }
      applyShaders(sprite, shaders);
    }

    /**/
    std::vector<std::string> Sfml::splitstring(const std::string& str,
                                               const char& ch) {
      std::string next;
      std::vector<std::string> res;

      for (std::string::const_iterator it = str.begin(); it != str.end();
           it++) {
        if (*it == ch) {
          if (!next.empty()) {
            res.push_back(next);
            next.clear();
          }
        } else {
          next += *it;
        }
      }
      if (!next.empty())
        res.push_back(next);
      return res;
    }
    /**/

    void Sfml::applyShaders(sf::Sprite& sprite,
                            std::vector<std::string>& shaderNames) {
      sf::RenderTexture renderTexture1;
      sf::RenderTexture renderTexture2;
      if (!renderTexture1.create(_windowSize.first, _windowSize.second) ||
          !renderTexture2.create(_windowSize.first, _windowSize.second)) {
        throw std::runtime_error("Failed to create render textures.");
      }

      sf::RenderTexture* front = &renderTexture1;
      sf::RenderTexture* back  = &renderTexture2;

      sprite.setPosition(sprite.getPosition().x + _windowSize.first / 2,
                         sprite.getPosition().y + _windowSize.second / 2);

      front->clear(sf::Color::Transparent);

      std::vector<std::string> shaderParts = splitstring(shaderNames[0], '|');
      if (_shaders.find(shaderParts[0]) == _shaders.end()) {
        throw std::runtime_error("Shader not found: " + shaderParts[0]);
      }

      for (int i = 1; i < shaderParts.size() - 1; i += 2) {
        _shaders[shaderParts[0]].setParameter(shaderParts[i].c_str(),
                                              std::stof(shaderParts[i + 1]));
      }
      front->draw(sprite, &_shaders[shaderParts[0].c_str() /*"Pixelate"*/]);
      front->display();

      for (std::size_t i = 1; i < shaderNames.size(); ++i) {
        shaderParts = splitstring(shaderNames[i], '|');
        if (_shaders.find(shaderParts[0]) == _shaders.end()) {
          throw std::runtime_error("Shader not found: " + shaderNames[i]);
        }

        for (int j = 1; j < shaderParts.size() - 1; j += 2) {
          _shaders[shaderParts[0]].setParameter(shaderParts[j].c_str(),
                                                std::stof(shaderParts[j + 1]));
        }

        back->clear(sf::Color::Transparent);

        back->draw(sf::Sprite(front->getTexture()),
                   &_shaders[shaderParts[0].c_str()]);
        back->display();
        std::swap(front, back);
      }

      sf::Sprite resultSprite(front->getTexture());
      resultSprite.setOrigin(_windowSize.first / 2, _windowSize.second / 2);

      _window.draw(resultSprite);

      front->clear(sf::Color::Transparent);
      back->clear(sf::Color::Transparent);
    }

    void Sfml::drawSprite(std::string animationName, std::size_t currentFrame,
                          int posX, int posY, float scaleX, float scaleY,
                          float rotation, RGBA mask,
                          std::vector<std::string> objectShaders,
                          bool addActive) {
      const zef::graph::Animation_t anim = _animations.at(animationName);

      auto& sp = _sprites.at(anim.SpriteSheet).first;
      sp.setTexture(_sprites.at(anim.SpriteSheet).second);
      sp.setTextureRect(
          sf::IntRect(anim.Size.first * currentFrame + anim.StartPos.first,
                      anim.StartPos.second * anim.Size.second, anim.Size.first,
                      anim.Size.second));
      sp.setColor(
          sf::Color(255 * mask.R, 255 * mask.G, 255 * mask.B, 255 * mask.A));
      sp.setRotation(rotation);

      sp.setOrigin(anim.Size.first / 2, anim.Size.second / 2);
      sp.setPosition(posX, posY);
      sp.setScale(scaleX, scaleY);

      _window.setView(_views["Default"]);
      //_window.draw(_sprites.at(anim.SpriteSheet).first);
       drawShaders(_sprites.at(anim.SpriteSheet).first, objectShaders,
                   addActive);
    }

    void Sfml::drawSpriteHUD(std::string animationName,
                             std::size_t currentFrame, int posX, int posY,
                             float scaleX, float scaleY, float rotation,
                             RGBA mask, std::vector<std::string> objectShaders,
                             bool addActive) {
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
      _sprites.at(anim.SpriteSheet).first.setRotation(rotation);

      _sprites.at(anim.SpriteSheet)
          .first.setOrigin(anim.Size.first / 2, anim.Size.second / 2);
      _sprites.at(anim.SpriteSheet).first.setPosition(posX, posY);
      _sprites.at(anim.SpriteSheet).first.setScale(scaleX, scaleY);

      _window.setView(_views["HUD"]);
      //    _window.draw(_sprites.at(anim.SpriteSheet).first);
      drawShaders(_sprites.at(anim.SpriteSheet).first, objectShaders,
                  addActive);
    }

    void Sfml::drawText(std::string textString, std::string fontName,
                        std::size_t fontSize, int posX, int posY, float scaleX,
                        float scaleY, float rotation, RGBA mask) {
      _fonts.find(fontName)->second.second.setFont(_fonts.find(fontName)->second.first);
      sf::Color color(255 * mask.R, 255 * mask.G, 255 * mask.B, 255 * mask.A);

      sf::FloatRect textRect = _fonts.find(fontName)->second.second.getLocalBounds();
      _fonts.find(fontName)->second.second.setOrigin(textRect.left + textRect.width / 2,
                     textRect.top + textRect.height / 2);
      _fonts.find(fontName)->second.second.setPosition(posX, posY);
      _fonts.find(fontName)->second.second.setScale(scaleX, scaleY);
      _fonts.find(fontName)->second.second.setFillColor(color);
      _fonts.find(fontName)->second.second.setRotation(rotation);

      _window.setView(_views["Default"]);
      _window.draw(_fonts.find(fontName)->second.second);
    }

    void Sfml::drawTextHUD(std::string textString, std::string fontName,
                           std::size_t fontSize, int posX, int posY,
                           float scaleX, float scaleY, float rotation,
                           RGBA mask) {
            _fonts.find(fontName)->second.second.setFont(_fonts.find(fontName)->second.first);
      sf::Color color(255 * mask.R, 255 * mask.G, 255 * mask.B, 255 * mask.A);

      sf::FloatRect textRect = _fonts.find(fontName)->second.second.getLocalBounds();
      _fonts.find(fontName)->second.second.setOrigin(textRect.left + textRect.width / 2,
                     textRect.top + textRect.height / 2);
      _fonts.find(fontName)->second.second.setPosition(posX, posY);
      _fonts.find(fontName)->second.second.setScale(scaleX, scaleY);
      _fonts.find(fontName)->second.second.setFillColor(color);
      _fonts.find(fontName)->second.second.setRotation(rotation);

      _window.setView(_views["HUD"]);
      _window.draw(_fonts.find(fontName)->second.second);
    }

    void Sfml::drawHPBar(float posX, float posY, float width, float height,
                         float value, RGBA backgroundColor,
                         RGBA foregroundColor) {
      _window.setView(_views["Default"]);
      _hpBar.draw(_window, _rectangle, posX, posY, width, height, value,
                  sf::Color(backgroundColor.R, backgroundColor.G,
                            backgroundColor.B, backgroundColor.A),
                  sf::Color(foregroundColor.R, foregroundColor.G,
                            foregroundColor.B, foregroundColor.A));
    }

    bool Sfml::playSound(std::string soundName, int volume) {
      auto soundIt = _sounds.find(soundName);

      if (soundIt == _sounds.end()) {
        return false;
      }

      auto& soundPair = soundIt->second;
      soundPair.first.setBuffer(soundPair.second);

      int globalVolume = 100;
      if (!getSetting("Volume").empty()) {
        globalVolume = std::atoi(getSetting("Volume").c_str());
      }
      soundPair.first.setVolume(volume * globalVolume / 100);
      soundPair.first.play();
      return true;
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

    std::pair<int,int> Sfml::getCameraPos(){
      sf::Vector2f center = _views["Default"].getCenter();
      return {static_cast<int>(center.x), static_cast<int>(center.y)};
    }

    void Sfml::updateUserInputs(utils::UserInputs& ui) {
      sf::Event evt;
      while (_window.pollEvent(evt)) {
        if (evt.type == evt.Closed) {
          std::cout << "mqkdsqkfdsjhkjqhfdsdsqkfjh\n";
          ui.keyboard.close = true;
        }
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
