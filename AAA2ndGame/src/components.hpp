/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

class compTest {
    public:
        compTest(int a) : _a(a) {
            std::cout << "creating " << a << std::endl;
        }

        int _a;
};




class NewDrawable {
    public:
        NewDrawable(std::string sp, float size, int layer) {
            _sp = sp;
            _size = size;
            _layer = layer;
            std::cout << "layer is : " << layer << std::endl;
            
        }

        std::string _sp;
        float _size;
        int _layer;
};

class Position {
    public:
        Position(float x, float y) : _x(x), _y(y) {

        }

        float _x;
        float _y;
};

class Vector {
    public:
        Vector(float x, float y) : _x(x), _y(y) {

        }

        float _x;
        float _y;
};

class Text {
    public:
        Text(std::string txt, int size) : _txt(txt), _size(size) {
            std::cout << "text is: " << txt << std::endl;
        }
    
    std::string _txt;
    int _size;

};

class Clickable {
    public:
        Clickable(int x, int y) : _x(x), _y(y) {

        }

    int _x;
    int _y;
};


class Respawn {
    public:
        Respawn(int respawn) : _respawn(respawn) {

        }

        int _respawn;
};

class Score {
    public:
        Score() {};

    int _score = 0;
    bool _update = false;
};

class Duck {
    public:
        Duck() {};
};

class FinalScore {
    public:
        FinalScore() {}

        int _fsc = 0;
};

#endif /* !COMPONENTS_HPP_ */
