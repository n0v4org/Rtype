
/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** components
*/

#ifndef ENGINE_MODULES_TIMER_COMPONENTS_HPP_
#define ENGINE_MODULES_TIMER_COMPONENTS_HPP_

#include <map>
#include <string>
#include <chrono>
#include <functional>

namespace zef
{
    class Engine;
    namespace comp
    {
        class timer {
        public:
            timer() {

            }

            void startTimer(const std::string& name) {
                _timers[name] = std::chrono::high_resolution_clock::now();
            }

            size_t get(const std::string& name) {
                return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _timers[name]).count();
            }

            std::map<std::string, std::chrono::_V2::system_clock::time_point> _timers;

        };
    } // namespace comp
} // namespace zef



#endif // ENGINE_MODULES_TIMER_COMPONENTS_HPP_