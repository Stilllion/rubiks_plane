#include "Game.h"

void Game::GetSelection()
{
	// Set selected row, col and selected_plane
	for(int i = 0; i < 6; ++i){
		for(int x = 0; x < 3; ++x){
			for(int y = 0; y < 3; ++y){
				if((*all_planes[i])[x][y].getGlobalBounds().contains(spr_selection.getPosition().x + 9, spr_selection.getPosition().y + 9))
				{
					selected_row = y;
					selected_col = x;
					selected_plane = i;
				}
			}
		}
	}
}


sf::Color getColor(char ch_color)
{
	if(ch_color == 'Y'){return sf::Color::Yellow;}
	if(ch_color == 'G'){return sf::Color::Green;}
	if(ch_color == 'R'){return sf::Color::Red;}
	if(ch_color == 'O'){return sf::Color(255,165,0);}
	if(ch_color == 'B'){return sf::Color::Blue;}
	if(ch_color == 'W'){return sf::Color::White;}
}


void Game::Paint()
{
	for(int i = 0; i < 6; ++i){
		for(int x = 0; x < 3; ++x){
			for(int y = 0; y < 3; ++y){
				(*all_planes[i])[x][y].setFillColor(getColor((*ch_all_planes[i])[x][y]));
			}
		}
	}
}


void Game::SwitchFirstAndLastRow(char ch_plane[3][3])
{
	char ch_temp[3][3];
	for(int i = 0; i < 3; ++i){
		for(int k = 0; k < 3; ++k){
			ch_temp[i][k] = ch_plane[i][k];			
		}
	}
	
	ch_plane[0][0] = ch_plane[0][2];
	ch_plane[1][0] = ch_plane[1][2];
	ch_plane[2][0] = ch_plane[2][2];
	
	ch_plane[0][2] = ch_temp[0][0];
	ch_plane[1][2] = ch_temp[1][0];
	ch_plane[2][2] = ch_temp[2][0];
}


void Game::SwitchFirstAndLastCol(char ch_plane[3][3])
{
	char ch_temp[3][3];
	for(int i = 0; i < 3; ++i){
		for(int k = 0; k < 3; ++k){
			ch_temp[i][k] = ch_plane[i][k];			
		}
	}
	
	ch_plane[0][0] = ch_plane[2][0];
	ch_plane[0][1] = ch_plane[2][1];
	ch_plane[0][2] = ch_plane[2][2];
	
	ch_plane[2][0] = ch_temp[0][0];
	ch_plane[2][1] = ch_temp[0][1];
	ch_plane[2][2] = ch_temp[0][2];
}


void Game::RotatePlaneCCW(char ch_plane[3][3])
{
	for (int i = 0; i < 1; ++i) { 
		for (int j = 0; j < 2; ++j) {   
			// Swap elements in clockwise direction 
			char temp = ch_plane[i][j]; 
			ch_plane[i][j] = ch_plane[i + 2 - j][i];
			ch_plane[i + 2 - j][i] = ch_plane[i + 2][i + 2 - j];
			ch_plane[i + 2][i + 2 - j] = ch_plane[i + j][i + 2];
			ch_plane[i + j][i + 2] = temp;		
		}
	}	
}


bool Game::IsValidMove(sf::Vector2f move_dest)
{
	
	for(int i = 0; i < 6; ++i){
		for(int x = 0; x < 3; ++x){
			for(int y = 0; y < 3; ++y){
				if(spr_selection.getPosition().x + move_dest.x == (*all_planes[i])[x][y].getPosition().x &&
				spr_selection.getPosition().y + move_dest.y == (*all_planes[i])[x][y].getPosition().y){
						return true;	
				}
			}
		}
	}
	return false;
}


void Game::Scrumble()
{
	bool tempHorizontal = horizontal;
	
	for(int i = 0; i < 20; ++i){
		
		int rotation_number = dist(mt);
		
		switch (rotation_number)
		{
			case 0: {
				U();
			}
			break;
			case 1: {
				D();
			}
			break;
			case 2: {
				F();
			}
			break;
			case 3: {
				R();
			}
			break;
			case 4: {
				L();
			}
			break;
			case 5: {
				B();
			}
			break;	
		}
		
		Move();
		direction = '-';
	}
	
	
	// Reset state
	direction = '-';
	selected_col = -1;
	selected_row = -1;
	selected_plane = -1;
	horizontal = tempHorizontal;
}

bool Game::IsSolved()
{
	for(int i = 0; i < 6; ++i){
		for(int x = 0; x < 3; ++x){
			for(int y = 0; y < 3; ++y){
				if((*ch_all_planes[i])[x][y] != (*ch_all_planes[i])[1][1]){
					return false;
				}
			}
		}
	}
	
	return true;
}


/*
	{
		char ch_selected_plane = ' ';
		
		if(selected_plane == 0){ ch_selected_plane = 'L'; }
		if(selected_plane == 1){ ch_selected_plane = 'R'; }
		if(selected_plane == 2){ ch_selected_plane = 'T'; }
		if(selected_plane == 3){ ch_selected_plane = 'B'; }
		if(selected_plane == 4){ ch_selected_plane = 'D'; }
		if(selected_plane == 5){ ch_selected_plane = 'F'; }
		
		std::cout << "Row, col, plane --> " << selected_row << ", " << selected_col << ", " << ch_selected_plane << std::endl;
		
		if (horizontal) {
			std::cout << "Direction, rotation --> " << direction << ", " << "horizontal" << std::endl;							
		} else {
			std::cout << "Direction, rotation --> " << direction << ", " << "vertical" << std::endl;
		}	
	}
	
	
	sf::Vector2f mp = window.mapPixelToCoords(static_cast<sf::Vector2i>(mouse_position));
	for(int i = 0; i < 6; ++i){
		for(int x = 0; x < 3; ++x){
			for(int y = 0; y < 3; ++y){
				mp = window.mapPixelToCoords(static_cast<sf::Vector2i>(mouse_position));
			
				if((*all_planes[i])[x][y].getGlobalBounds().contains(static_cast<sf::Vector2f>(mp))){
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						std::cout << "x, y " << x << " " << y << std::endl;
					}
				}
			}
		}
	}
*/