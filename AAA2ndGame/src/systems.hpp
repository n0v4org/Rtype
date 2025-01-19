/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_

#include "components.hpp"
#include "Engine.hpp"


//void testSys(zef::Engine& engine,  ecs::sparse_array<compTest>& cts) {
//    for (auto &&[i, ct]: ecs::indexed_zipper(cts)) {
//        std::cout << ct._a << std::endl;
//    }
//}

void drawNewDrawable(zef::Engine& engine, ecs::sparse_array<NewDrawable>& nds, ecs::sparse_array<Position>& pss) {
    std::vector<int> layers;
    for (auto &&[i, nd, pos]: ecs::indexed_zipper(nds, pss)) {
        layers.push_back(nd._layer);
    }
    std::sort(layers.begin(), layers.end());
    for (int l : layers) {
        
        for (auto &&[i, nd, pos]: ecs::indexed_zipper(nds, pss)) {
            if (nd._layer == l)
            engine.GraphLib->drawSprite(nd._sp, 0, pos._x, pos._y, nd._size, nd._size, 0.0f);
        }
    }
}

void drawText(zef::Engine& engine, ecs::sparse_array<Text>& txs, ecs::sparse_array<Position>& pss) {
    for (auto &&[i, txt, pos]: ecs::indexed_zipper(txs, pss)) {
        engine.GraphLib->drawTextHUD(txt._txt, "michelin", txt._size, pos._x, pos._y);
    }
}

void handleClickable(zef::Engine& engine, ecs::sparse_array<Clickable>& css, ecs::sparse_array<Position>& pss) {

    int mpx = engine.getUserInputs().mouse.x;
    int mpy = engine.getUserInputs().mouse.y;
    for (auto &&[i, cl, pos]: ecs::indexed_zipper(css, pss)) {
        if (mpx > pos._x - (cl._x/2) && mpx < pos._x + (cl._x/2) && mpy > pos._y - (cl._y/2) && mpy < pos._y + (cl._y/2)) {
            if (std::find(engine.getUserInputs().mouse._released.begin(),
                 engine.getUserInputs().mouse._released.end(), zef::utils::MouseButtons::Left) != engine.getUserInputs().mouse._released.end()) {
                engine.nsendEvent("onClick", i);
            }
            if (std::find(engine.getUserInputs().mouse._pressed.begin(),
                 engine.getUserInputs().mouse._pressed.end(), zef::utils::MouseButtons::Left) != engine.getUserInputs().mouse._pressed.end()) {
                engine.nsendEvent("clicked", i);
            }
        }
    }
}

void newMove(zef::Engine& engine, ecs::sparse_array<Position>& pss, ecs::sparse_array<Vector>& vts) {
    for (auto &&[i, pos, vec]: ecs::indexed_zipper(pss, vts)) {
        pos._x += vec._x;
        pos._y += vec._y;
    }
}

void handleRespawn(zef::Engine& engine, ecs::sparse_array<Respawn>& rss, ecs::sparse_array<Position>& pss, ecs::sparse_array<Vector>& vss) {
    for (auto &&[i, resp, pos, vec]: ecs::indexed_zipper(rss, pss, vss)) {
        resp._respawn -= engine.elapsed.count();
        if (resp._respawn <= 0) {
            engine.removeEntityComponent<Respawn>(ecs::Entity(i));

            pos._x = (rand() % 1000) - 500; 
            pos._y = 330; 

            vec._x = (rand() % 16) - 8;
            vec._y = (rand() % 16) - 8;
        }
    }
}

void handleScore(zef::Engine& engine, ecs::sparse_array<Score>& scs, ecs::sparse_array<Text>& txs) {
    for (auto &&[i, sc, txt]: ecs::indexed_zipper(scs, txs)) {
        if (sc._update) {
            txt._txt = std::to_string(sc._score);
            sc._update = false;
        }
    }
}


void bounceDuck(zef::Engine& engine, ecs::sparse_array<Duck>& dks, ecs::sparse_array<Position>& pss, ecs::sparse_array<Vector>& vts) {
    for (auto &&[i, dk, pos, vec]: ecs::indexed_zipper(dks, pss, vts)) {
        if (pos._x > 700 || pos._x < -700) {
            vec._x = -vec._x;
        }
        if (pos._y > 400 || pos._y < -500) {
            vec._y = -vec._y;
        }
    }
}

#endif /* !SYSTEMS_HPP_ */
