/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IDisplayModule
*/

#ifndef CLIENT_INCLUDE_GRAPHIC_IDISPLAYMODULE_HPP_
#define CLIENT_INCLUDE_GRAPHIC_IDISPLAYMODULE_HPP_

#include <cstdio>
#include <utility>
#include <chrono>
#include <string>
#include <map>
#include <vector>
#include <filesystem>


namespace rtype{


/**/
  typedef struct Event{
    bool A;
    bool B;
    bool C;
    bool D;
    bool E;
    bool F;
    bool G;
    bool H;
    bool I;
    bool J;
    bool K;
    bool L;
    bool M;
    bool N;
    bool O;
    bool P;
    bool Q;
    bool R;
    bool S;
    bool T;
    bool U;
    bool V;
    bool W;
    bool X;
    bool Y;
    bool Z;

    bool _1;
    bool _2;
    bool _3;
    bool _4;
    bool _5;
    bool _6;
    bool _7;
    bool _8;
    bool _9;
    bool _0;

    bool Enter;
    bool Escape;
    bool Shift;
    bool Control;
    bool Alt;
    bool CapsLock;

    bool ArrowUp;
    bool ArrowDown;
    bool ArrowLeft;
    bool ArrowRight;

    bool JoyStickUp;
    bool JoyStickDown;
    bool JoyStickLeft;
    bool JoyStickRight;

    bool LeftClick;
    bool RightClick;
    bool MiddleClick;
    int MouseX;
    int MouseY;
  }Event_t;
/**/


  typedef struct Animation{
    std::string AnimationName;
    std::pair<std::size_t,std::size_t> StartPos;
    std::pair<std::size_t,std::size_t> Size;
    int NbFrames;
    std::chrono::milliseconds TimeBetweenFrames;


  }Animation_t;

  typedef struct Entity{
    std::string SpriteName;
    std::string CurrentAnimationName;
    int CurrentFrame;
    std::vector<int> Position;
    std::pair<std::size_t,std::size_t> Scale;
    float Rotation;
    float AnimationSpeed;


  }Entity_t;

  class IDisplayModule{
    public:
      IDisplayModule(){};
      ~IDisplayModule(){};
      virtual void initialize() = 0;
      virtual void stop() = 0;
      virtual void clear() = 0;
      virtual void refresh() = 0;

      virtual Event_t getEvent() = 0;

      virtual void loadAssets(std::string)=0;

      virtual void storeAssetsPNG(std::string)=0;
      virtual void storeAssetsWAV(std::string)=0;
      virtual void storeAssetsTTF(std::string)=0;
      virtual void storeAssetsVERT(std::string)=0;

      virtual void playSound(std::string) = 0;
      virtual void drawText() = 0;
      virtual void drawSprite(std::string,int,int,int,int,float,float) = 0;

      virtual void saveAnimation(std::pair<std::size_t,std::size_t>,std::pair<std::size_t,std::size_t>)=0;

      virtual void playOnce(std::string,std::string)=0;
      virtual void playLoop(std::string,std::string)=0;

      virtual void setAnimationSpeed(std::string,float)=0;
      virtual void setScale(std::string,std::pair<float,float>)=0;
      virtual void setPosition(std::string,std::pair<std::size_t,std::size_t>)=0;
      virtual void setRotation(std::string,float)=0;

      virtual void moveCamera(std::vector<float>)=0;

    protected:
    private:
  };

}

#endif //CLIENT_INCLUDE_GRAPHIC_IDISPLAYMODULE_HPP_


