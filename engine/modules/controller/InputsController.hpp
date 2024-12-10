/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Controller
*/

#ifndef ENGINE_MODULES_CONTROLLER_INPUTSCONTROLLER_HPP_
#define ENGINE_MODULES_CONTROLLER_INPUTSCONTROLLER_HPP_

#include <vector>

namespace zef
{
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

        PAUSE
    };

    enum MouseButtons {
        Left,
        Right,
        Middle,
        XButton1,
        XButton2,
    };

    struct KeyboardInputs {
        std::vector<Keys> PressedKeys;
        std::vector<Keys> ReleasedKeys;
    };

    struct MouseInputs {
        float x;
        float y;
        std::vector<MouseButtons> PressedButtons;
        std::vector<MouseButtons> ReleasedButtons;
        int scrollDelta;
    };

    struct UserInputs {
        MouseInputs mouse;
        KeyboardInputs keyboard;
    };
    


} // namespace zef



#endif // ENGINE_MODULES_CONTROLLER_INPUTSCONTROLLER_HPP_
