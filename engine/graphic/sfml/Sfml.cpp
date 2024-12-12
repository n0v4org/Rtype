/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SFML DisplayModule
*/

#include "./Sfml.hpp"

namespace zef{
namespace graph{

  void Sfml::initialize(std::string assetFolderPath, std::string windowName) {

    _window.create(sf::VideoMode(_windowSize.first, _windowSize.second), windowName.c_str());

    if (!_window.isOpen()) {
      throw WindowCreationException();
    }

    sf::View view({0, 0}, {1920, 1080});
    sf::View HUD({0, 0}, {1920, 1080});
//    view.setCenter(0, 0);
//    HUD.setCenter(0,0);
	_views["Default"] = view;
	_views["HUD"] = HUD;

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

  void Sfml::drawSprite(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX, float scaleY, float rotation, float opacity) {
    const zef::graph::Animation_t anim = _animations.at(animationName);
    const sf::Texture &texture = _sprites.at(anim.SpriteSheet);
    sf::IntRect rect(anim.Size.first * currentFrame + anim.StartPos.first, anim.StartPos.second * anim.Size.second, anim.Size.first, anim.Size.second);
    sf::Color color(255, 255, 255, 255 * opacity);

    sf::Sprite sprite(texture, rect);
    sprite.setColor(color);
    sprite.setRotation(rotation);

    sprite.setOrigin(anim.Size.first / 2, anim.Size.second / 2);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);

    _window.setView(_views["Default"]);
    _window.draw(sprite);
  };

  void Sfml::drawSpriteHUD(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX, float scaleY, float rotation, float opacity) {
    const zef::graph::Animation_t anim = _animations.at(animationName);
    sf::Sprite sprite = _sprites.at(anim.SpriteSheet).first;
    sf::Texture texture = _sprites.at(anim.SpriteSheet).second;
    sf::IntRect rect(anim.Size.first * currentFrame + anim.StartPos.first, anim.StartPos.second * anim.Size.second, anim.Size.first, anim.Size.second);
    sf::Color color(255, 255, 255, 255 * opacity);

    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setColor(color);
    sprite.setRotation(rotation);

    sprite.setOrigin(anim.Size.first / 2, anim.Size.second / 2);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);

    _window.setView(_views["HUD"]);
    _window.draw(sprite);
  };

  void Sfml::drawText(std::string textString, std::string fontName,std::size_t fontSize, int posX, int posY, float scaleX, float scaleY, float rotation, float opacity) {
    sf::Font font = _fonts.find(fontName)->second;
    sf::Text text(textString, font, fontSize);

    text.setPosition(posX, posY);
    text.setScale(scaleX, scaleY);
    text.setRotation(rotation);

    /*setorigin middle*/

    _window.setView(_views["Default"]);
    _window.draw(text);
  };

  void Sfml::drawTextHUD(std::string textString, std::string fontName,std::size_t fontSize, int posX, int posY, float scaleX, float scaleY, float rotation, float opacity) {
    sf::Font font = _fonts.find(fontName)->second;
    sf::Text text(textString, font, fontSize);

    text.setPosition(posX, posY);
    text.setScale(scaleX, scaleY);
    text.setRotation(rotation);

    /*setorigin middle*/
    _window.setView(_views["HUD"]);
    _window.draw(text);
  };

  void Sfml::storeAssetsPNG(std::string assetPath) {
      sf::Texture texture;
      std::string assetName = assetPath.substr(assetPath.find_last_of("/\\") + 1);
      assetName = assetName.substr(0, assetName.size()-4);
      if(!texture.loadFromFile(assetPath.c_str())){
        throw AssetLoadException();
      }
      std::cout<<"Loading texture: "<<assetName<<std::endl;
      _sprites[assetName.c_str()] = texture;
  };
  void Sfml::storeAssetsWAV(std::string assetPath) {
    sf::SoundBuffer soundbuffer;
    std::string assetName = assetPath.substr(assetPath.find_last_of("/\\") + 1);
    assetName = assetName.substr(0, assetName.size()-4);

    if(!soundbuffer.loadFromFile(assetPath.c_str())){
      throw AssetLoadException();
    }
    _sounds[assetName.c_str()] = soundbuffer;
  };
  void Sfml::storeAssetsTTF(std::string assetPath) {
    sf::Font font;
    std::string assetName = assetPath.substr(assetPath.find_last_of("/\\") + 1);
    assetName = assetName.substr(0, assetName.size()-4);

    if(!font.loadFromFile(assetPath.c_str())){
      throw AssetLoadException();
    }
    _fonts[assetName.c_str()] = font;
  };
  void Sfml::storeAssetsVERT(std::string assetPath){
  };

  void Sfml::playSound(std::string soundName){
      sf::Sound sound;
      sf::SoundBuffer soundbuffer = _sounds.find(soundName)->second;
      sound.setBuffer(soundbuffer);
      sound.play();
  };

  //void Sfml::saveAnimation(std::string name, Animation_t animation){
  void Sfml::saveAnimation(std::string animationName, std::string spriteSheetName, std::size_t startTileX, std::size_t startTileY, std::size_t tileSizeX, std::size_t tileSizeY) {
      Animation_t animation{spriteSheetName, {startTileX, startTileY}, {tileSizeX, tileSizeY}};

      _animations[animationName.c_str()] = animation;
  };

  void Sfml::moveCamera(int X, int Y, int Z){
    if (!_window.getView().getViewport().width) {
        sf::View defaultView = _window.getDefaultView();
        _window.setView(defaultView);
    }
    sf::View view = _window.getView();

    _views["Default"].setCenter(_views["Default"].getCenter().x + X,_views["Default"].getCenter().y + Y);
    _views["Default"].move(X,Y);
    _views["Default"].zoom(1.0f + Z / 100.0f);
    _window.setView(_views["Default"]);

  };

  void Sfml::setCamera(int X, int Y, int Z){
    if (!_window.getView().getViewport().width) {
        sf::View defaultView = _window.getDefaultView();
        _window.setView(defaultView);
    }
    sf::View view = _window.getView();
    view.move(X,Y);
    view.zoom(1.0f + Z / 100.0f);
    _window.setView(view);

  };



  void Sfml::updateUserInputs(utils::UserInputs &ui) {
    sf::Event evt;
    while (_window.pollEvent(evt))
    {
      if (evt.type == evt.KeyPressed) {
        if (ui.keyboard._key_map[static_cast<utils::Keys>(evt.key.code)] == false)
          ui.keyboard._pressed.push_back(static_cast<utils::Keys>(evt.key.code));
        ui.keyboard._key_map[static_cast<utils::Keys>(evt.key.code)] = true;
      }
      if (evt.type == evt.KeyReleased) {
        ui.keyboard._key_map[static_cast<utils::Keys>(evt.key.code)] = false;
        ui.keyboard._released.push_back(static_cast<utils::Keys>(evt.key.code));
      }
      if (evt.type == evt.MouseButtonPressed) {
        if (ui.mouse._mb_map[static_cast<utils::MouseButtons>(evt.mouseButton.button)] == false)
          ui.mouse._pressed.push_back(static_cast<utils::MouseButtons>(evt.mouseButton.button));
        ui.mouse._mb_map[static_cast<utils::MouseButtons>(evt.mouseButton.button)] = true;
      }
      if (evt.type == evt.MouseButtonReleased) {
        ui.mouse._mb_map[static_cast<utils::MouseButtons>(evt.mouseButton.button)] = false;
        ui.mouse._released.push_back(static_cast<utils::MouseButtons>(evt.mouseButton.button));
      }

      sf::Vector2i mousePosWindow = sf::Mouse::getPosition(_window);
      sf::Vector2f mousePosInView = _window.mapPixelToCoords(mousePosWindow);

      ui.mouse.x = mousePosInView.x;
      ui.mouse.y = mousePosInView.y;
    }
  }


  UserInput Sfml::getEvent(){
    UserInput userInput;

    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          userInput.Close = true;
		if (event.type == sf::Event::KeyPressed) {
      		if (event.text.unicode == 3 ) { userInput.Pressed_D = true;}
      		if (event.text.unicode == 8 ) { userInput.Pressed_I = true;}
      		if (event.text.unicode == 9 ) { userInput.Pressed_J = true;}
      		if (event.text.unicode == 10) { userInput.Pressed_K = true;}
      		if (event.text.unicode == 11) { userInput.Pressed_L = true;}
      		if (event.text.unicode == 12) { userInput.Pressed_M = true;}
      		if (event.text.unicode == 15) { userInput.Pressed_P = true;}
      		if (event.text.unicode == 16) { userInput.Pressed_Q = true;}
      		if (event.text.unicode == 18) { userInput.Pressed_S = true;}
      		if (event.text.unicode == 25) { userInput.Pressed_Z = true;}
		}
    }
    return userInput;
  };

  IDisplayModule* entryPoint() {
    return new Sfml;
  }

}
}