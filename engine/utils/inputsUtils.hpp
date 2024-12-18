/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Controller
*/

#ifndef ENGINE_INPUTS_UTILS_HPP
#define ENGINE_INPUTS_UTILS_HPP

#include <vector>

namespace zef
{
    namespace utils {
        enum Keys {
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,

            NUM_0,
            NUM_1,
            NUM_2,
            NUM_3,
            NUM_4,
            NUM_5,
            NUM_6,
            NUM_7,
            NUM_8,
            NUM_9,

            Escape,
            LControl,
            LShift,
            LAlt,
            LSystem,
            RControl,
            RShift,
            RAlt,
            RSystem,
            Menu,
            LBracket,
            RBracket,
            Semicolon,
            Comma,
            Period,
            Apostrophe,
            Slash,
            Backslash,
            Grave,
            Equal,
            Hyphen,
            Space,
            Enter,
            Backspace,
            Tab,
            PageUp,
            PageDown,
            End,
            Home,
            Insert,
            Delete,
            Add,
            Subtract,
            Multiply,
            Divide,
            ArrowLeft,
            ArrowRight,
            ArrowUp,
            ArrowDown,

            NUMPAD_0,
            NUMPAD_1,
            NUMPAD_2,
            NUMPAD_3,
            NUMPAD_4,
            NUMPAD_5,
            NUMPAD_6,
            NUMPAD_7,
            NUMPAD_8,
            NUMPAD_9,

            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,

            PAUSE,
            __KEY_COUNT
        };

        enum MouseButtons {
            Left,
            Right,
            Middle,
            XButton1,
            XButton2,
            __MOUSEBUTTON_COUNT
        };

        struct KeyboardInputs {
            std::map<utils::Keys, bool> _key_map;
            std::vector<utils::Keys> _released;
            std::vector<utils::Keys> _pressed;
        };

        struct MouseInputs {
            float x;
            float y;
            std::map<utils::MouseButtons, bool> _mb_map;
            std::vector<MouseButtons> _pressed;
            std::vector<MouseButtons> _released;
            int scrollDelta;
        };

        class UserInputs {
            public:
                UserInputs() {
                    for (int k = A; k < __KEY_COUNT; k++) {
                        keyboard._key_map[static_cast<utils::Keys>(k)] = false;
                    }
                    for (int k = A; k < __MOUSEBUTTON_COUNT; k++) {
                        mouse._mb_map[static_cast<utils::MouseButtons>(k)] = false;
                    }
                }

                MouseInputs mouse;
                KeyboardInputs keyboard;
        };
    } // namespace utils
} // namespace zef



#endif // ENGINE_INPUTS_UTILS_HPP