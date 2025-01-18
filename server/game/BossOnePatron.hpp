/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** BossOnePatron
*/

#ifndef BOSSONEPATRON_HPP_
#define BOSSONEPATRON_HPP_

#include <iostream>
#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/components.hpp"
#include "modules/network/components.hpp"
#include "events.hpp"
#include "BlastPatron.hpp"
#include "BossOneMiniPatron.hpp"
#include "BossBulletPatron.hpp"

inline zef::comp::event_listener createBossOneEventListener() {
  // zef::comp::event_listener evtl;
  //
  // evtl.setEvent<SetEnemyVectorEvent>(
  //    [](zef::Engine& engine, size_t self, SetEnemyVectorEvent e) {
  //      auto& vec = engine.fetchEntityComponent<zef::comp::vector>(self);
  //      vec.x     = e.vx;
  //      vec.y     = e.vy;
  //    });
  //
  // evtl.setEvent<BossShoot>([](zef::Engine& engine, size_t self, BossShoot p)
  // {
  //  auto& bossPos = engine.fetchEntityComponent<zef::comp::position>(self);
  //
  //  size_t count = 20;
  //
  //  float amplitudeMax = 600.f;
  //
  //  float frequency = 1.f;
  //
  //  float offsetPhase = 0.3f;
  //
  //  for (size_t i = 0; i < count; i++) {
  //    float ratio       = static_cast<float>(i) / (count - 1);
  //    float myAmplitude = amplitudeMax * ratio;
  //
  //    float bulletX = bossPos.x - 70.f - i * 20.f;
  //    float bulletY = bossPos.y + 240.f;
  //
  //    ecs::Entity bullet = engine.instanciatePatron<BossBulletPatron>(
  //        bulletX, bulletY, 0.f, 0.f);
  //
  //    engine.addEntityComponent<SinusoidalAboveMotion>(bullet, bulletY,
  //                                                     myAmplitude,
  //                                                     frequency);
  //
  //    auto& sam = engine.fetchEntityComponent<SinusoidalAboveMotion>(bullet);
  //    sam.phase = (count - i) * offsetPhase;
  //  }
  //});
  //
  // evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath p) {
  //  auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);
  //  engine.instanciatePatron<BlastPatron>(pos.x, pos.y, 3.0f);
  //  engine.reg.kill_entity(ecs::Entity(self));
  //});
  //
  // evtl.setEvent<GetHittedByBullet>(
  //    [](zef::Engine& engine, size_t self, GetHittedByBullet p) {
  //      engine.addEntityComponent<Damaged>(ecs::Entity(self), 100 * 1000);
  //    });
  //
  // evtl.setEvent<zef::evt::startCollision>(
  //    [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
  //      engine.sendEvent<GetHittedByMonster>(p.other);
  //    });
  //
  // return evtl;
}

class BossOnePatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, 0.f, 0.f, 0.f);

    engine.addEntityComponent<Health>(self, 300, 300);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createBossOneEventListener());

    engine.addEntityComponent<Monster>(self);

    engine.addEntityComponent<zef::comp::replicable>(self, rep);

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 161 * 2, 212 * 3)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
    ecs::Entity miniboss =
        engine.instanciatePatron<BossOneMiniPatron>(x + 25, x / 3 - 150, 2);
    engine.sendEvent<MiniBossShoot>(miniboss, -6.f, 0.f);
  }
};

#endif  // BOSSONEPATRON_HPP_
