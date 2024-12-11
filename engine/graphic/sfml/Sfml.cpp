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

  void Sfml::initialize(std::string path) {

    _window.create(sf::VideoMode(_windowSize.first, _windowSize.second), "RType");

    if (!_window.isOpen()) {
      throw WindowCreationException();
      return;
    }
    _window.setFramerateLimit(60);

    loadAssets(path);
  }

  void Sfml::refresh() {
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

    //void Sfml::drawSprite(DrawableSprite_t toDraw) {
    void Sfml::drawSprite(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX, float scaleY, float rotation, float opacity) {
    const rtype::Animation_t anim = _animations.at(animationName);
    const sf::Texture &texture = _sprites.at(anim.SpriteSheet);
    sf::IntRect rect(anim.Size.first * currentFrame + anim.StartPos.first, anim.StartPos.second * anim.Size.second, anim.Size.first, anim.Size.second);
    sf::Color color(255, 255, 255, 255 * opacity);

    sf::Sprite sprite(texture, rect);
    sprite.setColor(color);
    sprite.setRotation(rotation);

    sprite.setOrigin(anim.Size.first / 2, anim.Size.second / 2);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);

    _window.draw(sprite);
  };

  //void Sfml::drawText(DrawableText_t toDraw) {
  void Sfml::drawText(std::string textString, std::string fontName,std::size_t fontSize, int posX, int posY, float scaleX, float scaleY, float rotation, float opacity) {
    sf::Font font = _fonts.find(fontName)->second;
    sf::Text text(textString, font, fontSize);

    text.setPosition(posX, posY);
    text.setScale(scaleX, scaleY);
    text.setRotation(rotation);

    /*setorigin X-left Y-middle*/

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

  void Sfml::playSound(std::string toPlay){
      sf::Sound sound;
      sf::SoundBuffer soundbuffer = _sounds.find(toPlay)->second;
      sound.setBuffer(soundbuffer);
      sound.play();
  };

  //void Sfml::saveAnimation(std::string name, Animation_t animation){
  void Sfml::saveAnimation(std::string name, std::string spriteSheet, std::size_t startTileX, std::size_t startTileY, std::size_t SizeX, std::size_t SizeY) {
      Animation_t animation{spriteSheet, {startTileX, startTileY}, {SizeX, SizeY}};

      _animations[name.c_str()] = animation;
  };

  void Sfml::moveCamera(int X, int Y, int Z){
    if (!_window.getView().getViewport().width) {
        sf::View defaultView = _window.getDefaultView();
        _window.setView(defaultView);
    }
    sf::View view = _window.getView();

    view.move(X,Y);
    view.zoom(1.0f + Z / 100.0f);
    _window.setView(view);

  };



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

}
}