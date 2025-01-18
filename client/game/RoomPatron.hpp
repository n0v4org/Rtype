/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RoomPatron
*/

#ifndef ROOMPATRON_HPP_
#define ROOMPATRON_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Engine.hpp"
#include "BasicWallPatron.hpp"
#include "BlockWallPatron.hpp"
#include "BossOnePatron.hpp"
#include "EnemyCrabPatron.hpp"
#include "EnemyPlanePatron.hpp"
#include "EnemyRobotPatron.hpp"
#include "EnemyTurretPatron.hpp"
#include "WaterWallPatron.hpp"

class RoomPatron {
public:
    static void instanciate(zef::Engine& engine, const ecs::Entity& self,
                            const std::string& configPath)
    {
        parseAndCreateEntities(engine, configPath);
    }

private:
    static void parseAndCreateEntities(zef::Engine& engine, const std::string& configPath)
    {
        std::ifstream file(configPath);
        if (!file.is_open()) {
            std::cerr << "Failed to open room config file: " << configPath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }

            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type.rfind("Wall", 0) == 0) {
                float x, y, scaleX, scaleY;
                float rotation;
                if (!(iss >> x >> y >> scaleX >> scaleY >> rotation)) {
                    std::cerr << "Invalid line for Wall : " << line << std::endl;
                    continue;
                }
                createWall(engine, type, x, y, scaleX, scaleY, rotation);

            } else if (type == "RepeatWall1" || type == "RepeatWall2" || type == "RepeatWall3") {
                parseRepeatWall(engine, type, iss, line);

            } else if (type == "Plane") {
                float x, y;
                if (!(iss >> x >> y)) {
                    std::cerr << "Invalid line for Plane : " << line << std::endl;
                    continue;
                }
                createPlane(engine, x, y);

            } else if (type == "Robot") {
                float x, y;
                if (!(iss >> x >> y)) {
                    std::cerr << "Invalid line for Robot : " << line << std::endl;
                    continue;
                }
                createRobot(engine, x, y);

            } else if (type == "Crab") {
                float x, y;
                if (!(iss >> x >> y)) {
                    std::cerr << "Invalid line for Crab : " << line << std::endl;
                    continue;
                }
                createCrab(engine, x, y);

            //} else if (type == "Tourette" || type == "Turret") {
            //    float x, y;
            //    if (!(iss >> x >> y)) {
            //        std::cerr << "Invalid line for Turret : " << line << std::endl;
            //        continue;
            //    }
            //    createTurret(engine, x, y);

            } else if (type == "Boss") {
                float x, y;
                if (!(iss >> x >> y)) {
                    std::cerr << "Invalid line for Boss : " << line << std::endl;
                    continue;
                }
                createBoss(engine, x, y);

            } else {
                std::cerr << "Unknown entity type: " << type << std::endl;
            }
        }
        file.close();
    }


    static void createWall(zef::Engine& engine, 
                           const std::string& wallType,
                           float x, float y, 
                           float scaleX, float scaleY, float rotation)
    {
        if (wallType == "Wall1") {
            engine.instanciatePatron<BasicWallPatron>(x, y, scaleX, scaleY, rotation);
        } else if (wallType == "Wall2") {
            engine.instanciatePatron<BlockWallPatron>(x, y, scaleX, scaleY, rotation);
        } else if (wallType == "Wall3") {
            engine.instanciatePatron<WaterWallPatron>(x, y, scaleX, scaleY, rotation);
        } else {
            std::cerr << "Unknown wall type: " << wallType << std::endl;
        }
    }

    static void parseRepeatWall(zef::Engine& engine, const std::string& type,
                                std::istringstream& iss, const std::string& line)
    {
        float startX, startY;
        int count;
        float spacingX, spacingY;
        float scaleX=1.f, scaleY=1.f, rotation=0.f;

        if (!(iss >> startX >> startY >> count >> spacingX >> spacingY)) {
            std::cerr << "Invalid line for RepeatWall : " << line << std::endl;
            return;
        }
        iss >> scaleX >> scaleY >> rotation;

        for (int i = 0; i < count; i++) {
            float x = startX + i*spacingX;
            float y = startY + i*spacingY;

            if (type == "RepeatWall1") {
                engine.instanciatePatron<BasicWallPatron>(x, y, scaleX, scaleY, rotation);
            } else if (type == "RepeatWall2") {
                engine.instanciatePatron<BlockWallPatron>(x, y, scaleX, scaleY, rotation);
            } else if (type == "RepeatWall3") {
                engine.instanciatePatron<WaterWallPatron>(x, y, scaleX, scaleY, rotation);
            }
        }
    }

    static void createPlane(zef::Engine& engine, float x, float y)
    {
        ecs::Entity plane = engine.instanciatePatron<EnemyPlanePatron>(x, y, 0);
        engine.sendEvent<PlaneShootEvent>(plane, -5.f, 0.f);
        engine.sendEvent<SetEnemyVectorEvent>(plane, -3.f, 0.f);

    }

    static void createRobot(zef::Engine& engine, float x, float y)
    {
        ecs::Entity robot = engine.instanciatePatron<EnemyRobotPatron>(x, y, 0);
        engine.sendEvent<RobotShoot>(robot);
        engine.sendEvent<SetEnemyVectorEvent>(robot, -1.f, 0.f);
    }

    static void createCrab(zef::Engine& engine, float x, float y)
    {
        ecs::Entity crab = engine.instanciatePatron<EnemyCrabPatron>(x, y, 0);
        engine.sendEvent<SetEnemyVectorEvent>(crab, -4.f, 0.f);
    }

    //static void createTurret(zef::Engine& engine, float x, float y)
    //{
    //    engine.instanciatePatron<EnemyTurretPatron>(x, y, 0);
    //}

    static void createBoss(zef::Engine& engine, float x, float y)
    {
        ecs::Entity boss = engine.instanciatePatron<BossOnePatron>(x, y, 0);
        engine.sendEvent<BossShoot>(boss);
        engine.sendEvent<SetEnemyVectorEvent>(boss, 0.f, 0.f);
    }
};

#endif // ROOMPATRON_HPP_
