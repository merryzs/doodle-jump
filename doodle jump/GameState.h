#pragma once


enum class GameState
{
    Main_Menu,
    Play,
    Game_Over,
    Pause,
    win
};

extern GameState currentState;