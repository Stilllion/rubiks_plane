#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <time.h>
#include <random>
#include <array>
#include <chrono>

struct Game
{
	Game();
	
	// RNDN generator
	std::mt19937 mt;
	std::uniform_int_distribution<int> dist;
		
	void Update();
	void HandleInput();
	void Render();
	
	void Move();
	void Move_LFRB();
	void Move_TFDB();
	void Move_TLDR();
	
	void Paint();
	
	void RotatePlaneCCW(char ch_plane[3][3]);
	
	void SwitchFirstAndLastRow(char ch_plane[3][3]);
	void SwitchFirstAndLastCol(char ch_plane[3][3]);
	
	void GetSelection();
	
	bool IsValidMove(sf::Vector2f move_dest);	
	bool IsSolved();
	
	// uhh, rotations
	void R();
	void L();
	void F();
	void D();
	void B();
	void U();
	void Rprime();
	void Lprime();
	void Fprime();
	void Uprime();
	void Dprime();
	void Bprime();
	
	void Scrumble();
	 	
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;
	sf::Time elapsed;
	
	bool button_released = true;
		
	sf::RectangleShape top[3][3];
	sf::RectangleShape back[3][3];
	sf::RectangleShape front[3][3];
	sf::RectangleShape down[3][3];
	sf::RectangleShape right[3][3];
	sf::RectangleShape left[3][3];
	
	
	char ch_top[3][3];
	char ch_back[3][3];
	char ch_front[3][3];
	char ch_down[3][3];
	char ch_right[3][3];
	char ch_left[3][3];
	
	
	// Pointer arrays 
	char (*ch_LFRB[4])[3][3];
	char (*ch_TLDR[4])[3][3];
	char (*ch_TFDB[4])[3][3];
	char (*ch_all_planes[6])[3][3];

	
	sf::RectangleShape (*all_planes[6])[3][3];
			
	sf::Vector2f pointsOfSelectorRotations[6];
	
	int selected_row = -1;
	int selected_col = -1;
	int selected_plane = -1;
	char direction = '-';
	sf::Vector2f total_dist;
	
	sf::Sprite spr_selection;
	sf::Texture textr_selection;
	sf::Sprite selection_arr[3];
	bool was_released = true;
	
	// Orientation of selection
	bool horizontal = true;
	bool rotated = false;
	
	
	int moves = 0;
	sf::Time solving_time;
	sf::Clock solving_clock;
	int minutes = 0;
	
	
	// TEXT
	sf::Font font;
	sf::Text timer_text;
	sf::Text moves_text;
	sf::Text keys_text;
	
	bool start = false;
	
	bool scrumbling = true;
	
	sf::SoundBuffer sound_buffer;
	sf::Sound turn_sound;
	
	bool lost_focus = false;
	bool paused = false;
	
	int width = 660;
	int height = 700;
};