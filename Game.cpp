#include "Game.h"

#define mouse_position static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))

Game::Game() : dist(0, 6)
{
	window.create(sf::VideoMode(width, height), "Rubik's Plane!");
	// window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);
	
	srand(time(0));
	
	pointsOfSelectorRotations[0] = sf::Vector2f(275, 200);
	pointsOfSelectorRotations[1] = sf::Vector2f(440, 200);
	pointsOfSelectorRotations[2] = sf::Vector2f(110, 200);
	pointsOfSelectorRotations[3] = sf::Vector2f(275, 365);
	pointsOfSelectorRotations[4] = sf::Vector2f(275, 35);
	pointsOfSelectorRotations[5] = sf::Vector2f(275, 530);
	
	sound_buffer.loadFromFile("rubik.wav");
	turn_sound.setBuffer(sound_buffer);
	
	// Init sides 
	sf::RectangleShape piece(sf::Vector2f(50, 50));
	piece.setOrigin(25, 25);
	
	// TOP
	piece.setFillColor(sf::Color(255, 255, 255));
	for(int x = 0; x < 3; ++x){
		for(int y = 0; y < 3; ++y){
			piece.setPosition(sf::Vector2f((x*55)+275, y*55+35));
			top[x][y] = piece;
			ch_top[x][y] = 'W';
			
		}
	}
	
	// FRONT
	piece.setFillColor(sf::Color::Red);
	for(int x = 0; x < 3; ++x){
		for(int y = 0; y < 3; ++y){
			piece.setPosition(sf::Vector2f((x*55)+275, y*55+165+35));
			front[x][y] = piece;
			ch_front[x][y] = 'R';
		}
	}

	// DOWN
	piece.setFillColor(sf::Color::Yellow);
	
	piece.setPosition(sf::Vector2f(0*55+275, 2*55+330+35));
	down[0][0] = piece;

	piece.setPosition(sf::Vector2f(0*55+275, 1*55+330+35));
	down[0][1] = piece;

	piece.setPosition(sf::Vector2f(0*55+275, 0*55+330+35));
	down[0][2] = piece;

	piece.setPosition(sf::Vector2f(1*55+275, 2*55+330+35));
	down[1][0] = piece;

	piece.setPosition(sf::Vector2f(1*55+275, 1*55+330+35));
	down[1][1] = piece;

	piece.setPosition(sf::Vector2f(1*55+275, 0*55+330+35));
	down[1][2] = piece;

	piece.setPosition(sf::Vector2f(2*55+275, 2*55+330+35));
	down[2][0] = piece;

	piece.setPosition(sf::Vector2f(2*55+275, 1*55+330+35));
	down[2][1] = piece;

	piece.setPosition(sf::Vector2f(2*55+275, 0*55+330+35));
	down[2][2] = piece;

	for(int x = 0; x < 3; ++x){
		for(int y = 0; y < 3; ++y){
			ch_down[x][y] = 'Y';
		}
	}
	
	// BACK
	piece.setFillColor(sf::Color(255,128,0));
		
	piece.setPosition(sf::Vector2f(0*55+275, 2*55+495+35));
	back[0][0] = piece;
	
	piece.setPosition(sf::Vector2f(0*55+275, 1*55+495+35));
	back[0][1] = piece;
	
	piece.setPosition(sf::Vector2f(0*55+275, 0*55+495+35));
	back[0][2] = piece;
	
	piece.setPosition(sf::Vector2f(1*55+275, 2*55+495+35));
	back[1][0] = piece;
	
	piece.setPosition(sf::Vector2f(1*55+275, 1*55+495+35));
	back[1][1] = piece;
	
	piece.setPosition(sf::Vector2f(1*55+275, 0*55+495+35));
	back[1][2] = piece;
	
	piece.setPosition(sf::Vector2f(2*55+275, 2*55+495+35));
	back[2][0] = piece;
	
	piece.setPosition(sf::Vector2f(2*55+275, 1*55+495+35));
	back[2][1] = piece;
	
	piece.setPosition(sf::Vector2f(2*55+275, 0*55+495+35));
	back[2][2] = piece; 
	
	for(int x = 0; x < 3; ++x){
		for(int y = 0; y < 3; ++y){
			ch_back[x][y] = 'O';
		}
	}
	
	// LEFT
	piece.setFillColor(sf::Color::Green);
	for(int x = 0; x < 3; ++x){
		for(int y = 0; y < 3; ++y){
			piece.setPosition(sf::Vector2f(x*55+110, y*55+165+35));
			left[x][y] = piece;
			ch_left[x][y] = 'G';
		}
	}
	
	// RIGHT
	piece.setFillColor(sf::Color::Blue);
	for(int x = 0; x < 3; ++x){
		for(int y = 0; y < 3; ++y){
			piece.setPosition(sf::Vector2f(x*55+440, y*55+165+35));
			right[x][y] = piece;
			ch_right[x][y] = 'B';
		}
	}
	
	ch_LFRB[0] = &ch_left;
	ch_LFRB[1] = &ch_front;
	ch_LFRB[2] = &ch_right;
	ch_LFRB[3] = &ch_back;
	
	ch_TFDB[0] = &ch_top;
	ch_TFDB[1] = &ch_front;
	ch_TFDB[2] = &ch_down;
	ch_TFDB[3] = &ch_back;
	
	ch_TLDR[0] = &ch_top;
	ch_TLDR[1] = &ch_left;
	ch_TLDR[2] = &ch_down;
	ch_TLDR[3] = &ch_right;
	        
	
	all_planes[0] = &left;
	all_planes[1] = &right;
	all_planes[2] = &top;
	all_planes[3] = &back;
	all_planes[4] = &down;
	all_planes[5] = &front;
		
	
	ch_all_planes[0] = &ch_left;
	ch_all_planes[1] = &ch_right;
	ch_all_planes[2] = &ch_top;
	ch_all_planes[3] = &ch_back;
	ch_all_planes[4] = &ch_down;
	ch_all_planes[5] = &ch_front;
	
	textr_selection.loadFromFile("selection.png");
	spr_selection.setTexture(textr_selection);
	spr_selection.setOrigin(26, 26);
	spr_selection.setPosition(front[0][0].getPosition());
	
	font.loadFromFile("Roboto-Regular.ttf");
	
	moves_text.setFont(font);
	moves_text.setCharacterSize(18);
	moves_text.setFillColor(sf::Color::White);
	moves_text.setString("Moves: 0");
	moves_text.setPosition(50, 50);
	
	timer_text.setFont(font);
	timer_text.setCharacterSize(18);
	timer_text.setFillColor(sf::Color::White);
	timer_text.setString("Time: 0.0");
	timer_text.setPosition(520, 50);
	
	keys_text.setFont(font);
	keys_text.setCharacterSize(15);
	keys_text.setFillColor(sf::Color::White);
	keys_text.setString(" WASD - move selector \n R - rotate selector \n Arrows - rotate selected face \n LShift + S - scrumble \n Space - start timer, pause");
	keys_text.setPosition(435, 550);


	// Random number seed
	mt.seed(std::time(0));
}


void Game::Update()
{
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
		}
		if(event.type == sf::Event::Resized){
			sf::Vector2f new_size = static_cast<sf::Vector2f>(window.getSize());
			new_size.y = new_size.x / new_size.y * new_size.y;
			
			window.setSize(static_cast<sf::Vector2u>(new_size));
		}
		if (event.type == sf::Event::LostFocus) {
			lost_focus = true;
			paused = true;
		}
		
		if (event.type == sf::Event::GainedFocus) {
			lost_focus = false;
		//	paused = false;
//			solving_clock.restart();
		}
	}
	
	if (!scrumbling && !paused)
	{		
		moves_text.setString("Moves: " + std::to_string(moves));
		
		//solving_time = solving_clock.getElapsedTime();
		solving_time += solving_clock.restart();
	
		if ((int) solving_time.asSeconds() / 60 == 1) {
			++minutes;
			solving_time = solving_clock.restart();
		}
		
		std::string time_as_string = std::to_string(minutes) + ":" + std::to_string(solving_time.asSeconds());
		// Remove unneceseray digits
		time_as_string.pop_back();
		time_as_string.pop_back();
		time_as_string.pop_back();
		time_as_string.pop_back();

		timer_text.setString("Time: " + time_as_string);		
	}
	
	GetSelection();

	// Determine selected plane/row/col IF direction != 0 MOVE() then PAINT()
	if(direction != '-'){
		Move();
		direction = '-';
	}
	
	Paint();
	
	// Check if solved
	if (IsSolved() && !scrumbling) {
		// Means timer stops
		scrumbling = true;
		timer_text.setFillColor(sf::Color::Green);
	}
}


void Game::Move()
{
	if(horizontal)
	{
		// Front, left, right, back
		if(selected_plane == 5 || selected_plane == 0 || selected_plane == 1 || selected_plane == 3){
			Move_LFRB();
		}
		// Top, down
		if(selected_plane == 4 || selected_plane == 2){
			Move_TLDR();
		}
	}

	if(!horizontal)
	{
		// Front, top, back, down
		if(selected_plane == 5 || selected_plane == 2 || selected_plane == 3 || selected_plane == 4){
			Move_TFDB();
		}
		// left, right the most troublesome case
		if(selected_plane == 0 || selected_plane == 1)
		{	
			if(selected_plane == 0){
				selected_row = selected_col;
				
				if(direction == 'U'){
					direction = 'R';
				}
				
				if(direction == 'D'){
					direction = 'L';
				}
				
			} else {
				
				if(direction == 'U'){
					direction = 'L';
				}
				
				if(direction == 'D'){
					direction = 'R';
				}
				
				if(selected_col == 0){
					selected_row = 2;
				}
				if(selected_col == 1){
					selected_row = 1;
				}
				if(selected_col == 2){
					selected_row = 0;
				}
			}
			
			Move_TLDR();
		}
	}	
}

void Game::HandleInput()
{	
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::R) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{ 
		was_released = true;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && was_released){
		
		if(!scrumbling){
			if(!paused){
				paused = true;
			} else {
				paused = false;
				solving_clock.restart();
			}
		}
		
		if(scrumbling){
			scrumbling = false;
			moves = 0;
			solving_time = sf::seconds(0);
			timer_text.setFillColor(sf::Color::White);
			solving_clock.restart();
		}
		
		was_released = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && was_released){
			Scrumble();
			was_released = false;
		}
	}
	   
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && was_released){
		
		bool valid_rotation = false;
		
		for(int i = 0; i < 6; ++i){
			if(spr_selection.getPosition() == pointsOfSelectorRotations[i]){
				valid_rotation = true;
				break;
			}
		}
		
		if(!valid_rotation) {
			
			sf::Vector2f closest_pos(10000, 10000);
			float closest_dist = 100000;
			
			for(int i = 0; i < 6; ++i){
				float dist = std::pow(std::abs(spr_selection.getPosition().x - pointsOfSelectorRotations[i].x), 2) +
							 std::pow(std::abs(spr_selection.getPosition().y - pointsOfSelectorRotations[i].y), 2);
							 
				if(dist < closest_dist){
					closest_pos = pointsOfSelectorRotations[i];
					closest_dist = dist;
				}
			}	
			spr_selection.setPosition(closest_pos);
		}
				
		if(horizontal){
			horizontal = false;
		} else {
			horizontal = true;
		}
		
		was_released = false;
		if(spr_selection.getRotation() == 90){
			spr_selection.rotate(-90);
			return;
		}
		spr_selection.rotate(90);	
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && was_released)
	{
		if(!horizontal){
			if(IsValidMove(sf::Vector2f(0, -55 * 3))){
				spr_selection.move(0, -55 * 3);
			}
		} else {
			if(IsValidMove(sf::Vector2f(0, -55))){
				spr_selection.move(0, -55);							
			}
		}
		
		was_released = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && was_released)
	{	
		if(!horizontal){
			if(IsValidMove(sf::Vector2f(0, 55 * 3))){	
				spr_selection.move(0, 55 * 3);
			}
		} else {
			if(IsValidMove(sf::Vector2f(0, 55))){				
				spr_selection.move(0, 55);			
			}
		}
		
		was_released = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && was_released)
	{
		if(horizontal){
			if(IsValidMove(sf::Vector2f(-55 * 3, 0))){
				spr_selection.move(-55 * 3, 0);				
			}
		} else {
			if(IsValidMove(sf::Vector2f(-55, 0))){
				spr_selection.move(-55, 0);				
			}
		}
	
		was_released = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && was_released)
	{
		if(horizontal){
			if(IsValidMove(sf::Vector2f(55 * 3, 0))){
				spr_selection.move(55 * 3, 0);
			}
		} else {
			if(IsValidMove(sf::Vector2f(55, 0))){
				spr_selection.move(55, 0);
			}
		}
		
		was_released = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && was_released)
	{
		direction = 'U';
		was_released = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && was_released)
	{
		direction = 'D';
		was_released = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && was_released){
		direction = 'L';
		was_released = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && was_released)
	{
		direction = 'R';
		was_released = false;
	}
}

void Game::Render()
{
	window.clear(sf::Color::Black);

	for(int i = 0; i < 6; ++i){
		for(int x = 0; x < 3; ++x){
			for(int y = 0; y < 3; ++y){
				window.draw((*all_planes[i])[x][y]);
			}
		}
	}
	
	window.draw(spr_selection);
	
	window.draw(timer_text);
	window.draw(moves_text);
	window.draw(keys_text);
	
	window.display();
}