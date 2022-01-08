#include "Game.h"

void Game::Move_LFRB()
{
	char ch_L_temp[3] {'-'};
	for(int i = 0; i < 3; ++i){
		ch_L_temp[i] = (*ch_LFRB[0])[i][selected_row];	
	}
	
	// Rotating top row of the FRONT plane makes TOP plane rotate
	if(selected_row == 0)
	{
		// Move to the right
		if(direction == 'R'){
			// One CCW rotation
			RotatePlaneCCW(ch_top);
		}
		// Move to the left
		if(direction == 'L'){
			// One CW rotation
			for(int i = 0; i < 3; ++i){
				RotatePlaneCCW(ch_top);
			}
		}
	}
	
	// Same goes for FRONT and DOWN
	if(selected_row == 2)
	{
		// Move to the left
		if(direction == 'L'){
			// One CCW rotation
			for(int i = 0; i < 3; ++i){
				RotatePlaneCCW(ch_down);
			}
		}
		// Move to the right
		if(direction == 'R'){
			// One CW rotation
			RotatePlaneCCW(ch_down);
		}
	}
	
	// Move to the right
	if(direction == 'R')
	{
		SwitchFirstAndLastCol(ch_left);
		for(int i = 0; i < 3; ++i){
			(*ch_LFRB[0])[i][selected_row] = (*ch_LFRB[3])[i][selected_row];
		}
		SwitchFirstAndLastCol(ch_left);
		
		SwitchFirstAndLastCol(ch_right);
		for(int i = 0; i < 3; ++i){
			(*ch_LFRB[3])[i][selected_row] = (*ch_LFRB[2])[i][selected_row];
		}
		SwitchFirstAndLastCol(ch_right);
		
		for(int i = 0; i < 3; ++i){
			(*ch_LFRB[2])[i][selected_row] = (*ch_LFRB[1])[i][selected_row];
			(*ch_LFRB[1])[i][selected_row] = ch_L_temp[i];
		}
		
		turn_sound.play();
		++moves;
	}
	
	// Moved to the left
	if(direction == 'L')
	{
		for(int i = 0; i < 3; ++i){	
			(*ch_LFRB[0])[i][selected_row] = (*ch_LFRB[1])[i][selected_row];
			(*ch_LFRB[1])[i][selected_row] = (*ch_LFRB[2])[i][selected_row];
		}
		
		SwitchFirstAndLastCol(ch_right);
		for(int i = 0; i < 3; ++i){	
			(*ch_LFRB[2])[i][selected_row] = (*ch_LFRB[3])[i][selected_row];
		}
		SwitchFirstAndLastCol(ch_right);
		
		SwitchFirstAndLastCol(ch_back);
		for(int i = 0; i < 3; ++i){	
			(*ch_LFRB[3])[i][selected_row] = ch_L_temp[i];
		}
		SwitchFirstAndLastCol(ch_back);
		
		turn_sound.play();
		++moves;
	}

}

void Game::Move_TFDB()
{
	char ch_T_temp[3] {'-'};
	
	for(int i = 0; i < 3; ++i){
		ch_T_temp[i] = (*ch_TFDB[0])[selected_col][i];
	}

	if(selected_col == 0)
	{
		// Move down
		if(direction == 'D'){
			// One CW rotation (3 CCW)
			for(int i = 0; i < 3; ++i){
				RotatePlaneCCW(ch_left);
			}
		}
		// Move up
		if(direction == 'U'){
			// One CCW rotation
			RotatePlaneCCW(ch_left);
		}
	}
	
	if(selected_col == 2)
	{
		// Move down
		if(direction == 'D'){
			// One CCW rotation
			RotatePlaneCCW(ch_right);
		}
		// Move up
		if(direction == 'U'){
			// One CW rotation (3 CCW)
			for(int i = 0; i < 3; ++i){
				RotatePlaneCCW(ch_right);
			}
		}
	}
		
	// Move down
	if(direction == 'D')
	{
		SwitchFirstAndLastRow(ch_top);
		for(int b = 0; b < 3; ++b){
			(*ch_TFDB[0])[selected_col][b] = (*ch_TFDB[3])[selected_col][b];
			(*ch_TFDB[3])[selected_col][b] = (*ch_TFDB[2])[selected_col][b];
		}
		SwitchFirstAndLastRow(ch_top);
		
		SwitchFirstAndLastRow(ch_down);
		for(int b = 0; b < 3; ++b){
			(*ch_TFDB[2])[selected_col][b] = (*ch_TFDB[1])[selected_col][b];
		}
		SwitchFirstAndLastRow(ch_down);

		for(int b = 0; b < 3; ++b){
			(*ch_TFDB[1])[selected_col][b] = ch_T_temp[b];
		}
		
		turn_sound.play();
		++moves;
	}
		
	// Moved up
	if(direction == 'U')
	{
		for(int b = 0; b < 3; ++b){
			(*ch_TFDB[0])[selected_col][b] = (*ch_TFDB[1])[selected_col][b];
		}
		
		SwitchFirstAndLastRow(ch_down);
		for(int b = 0; b < 3; ++b){
			(*ch_TFDB[1])[selected_col][b] = (*ch_TFDB[2])[selected_col][b];
		}
		SwitchFirstAndLastRow(ch_down);
		
		for(int b = 0; b < 3; ++b){
			(*ch_TFDB[2])[selected_col][b] = (*ch_TFDB[3])[selected_col][b];							
		}
		
		SwitchFirstAndLastRow(ch_back);
		for(int b = 0; b < 3; ++b){
			(*ch_TFDB[3])[selected_col][b] = ch_T_temp[b];
		}
		SwitchFirstAndLastRow(ch_back);
		
		turn_sound.play();
		++moves;
	}
}

void Game::Move_TLDR()
{
	char ch_T_temp[3] {'-'};
	
	for(int i = 0; i < 3; ++i){
		ch_T_temp[i] = (*ch_TFDB[0])[i][selected_row];
	}
	
	if(selected_row == 0){
		// Move to the right
		if(direction == 'R'){
			// One CCW rotation
			// NOT SURE YET
			for(int i = 0; i < 3; ++i){
				RotatePlaneCCW(ch_back);
			}
		}
		// Move to the left
		if(direction == 'L'){
			// One CW rotation
			//for(int i = 0; i < 3; ++i){
				RotatePlaneCCW(ch_back);
			//}
		}
	}
	
	// Same goes for FRONT and DOWN
	if(selected_row == 2){
		// Move to the left
		if(direction == 'L'){
			// One CCW rotation
			RotatePlaneCCW(ch_front);
		}
		// Move to the right
		if(direction == 'R'){
			// One CW rotation
			for(int i = 0; i < 3; ++i){
				RotatePlaneCCW(ch_front);
			}
		}
	}
	
	// TOP 1st row becomes left's first col and so on
	// DOWN Last row becomes right last col and so on
	if(direction == 'L'){
		if(selected_row == 0)
		{
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[0])[b][selected_row] = (*ch_TLDR[3])[2][b];
			}
			
			SwitchFirstAndLastRow(ch_right);			
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[3])[2][b] = (*ch_TLDR[2])[b][0];
				(*ch_TLDR[2])[b][0] = (*ch_TLDR[1])[0][b];
			}
			SwitchFirstAndLastRow(ch_right);
			
			
			SwitchFirstAndLastRow(ch_left);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[1])[0][b] = ch_T_temp[b];
			}
			SwitchFirstAndLastRow(ch_left);
			
			turn_sound.play();
			++moves;
		}
		
		if(selected_row == 1)
		{
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[0])[b][selected_row] = (*ch_TLDR[3])[1][b];
			}
			
			SwitchFirstAndLastRow(ch_right);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[3])[1][b] = (*ch_TLDR[2])[b][1];
				(*ch_TLDR[2])[b][1] = (*ch_TLDR[1])[1][b];
			}
			SwitchFirstAndLastRow(ch_right);
			
			SwitchFirstAndLastRow(ch_left);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[1])[1][b] = ch_T_temp[b];
			}
			SwitchFirstAndLastRow(ch_left);
			
			turn_sound.play();
			++moves;
		}
		
		if(selected_row == 2)
		{
			for(int b = 0; b < 3; ++b){	
				(*ch_TLDR[0])[b][selected_row] = (*ch_TLDR[3])[0][b];
			}
			
			SwitchFirstAndLastRow(ch_right);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[3])[0][b] = (*ch_TLDR[2])[b][2];
				(*ch_TLDR[2])[b][2] = (*ch_TLDR[1])[2][b];
			}
			SwitchFirstAndLastRow(ch_right);
			
			SwitchFirstAndLastRow(ch_left);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[1])[2][b] = ch_T_temp[b];
			}
			SwitchFirstAndLastRow(ch_left);
			
			turn_sound.play();
			++moves;
		}	
	}

	// TOP 1st row becomes right's last col and so on
	// DOWN Last row becomes right first col and so on
	if(direction == 'R'){
		if(selected_row == 0)
		{
			SwitchFirstAndLastCol(ch_top);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[0])[b][selected_row] = (*ch_TLDR[1])[0][b];
				(*ch_TLDR[1])[0][b] = (*ch_TLDR[2])[b][0];
			}
			SwitchFirstAndLastCol(ch_top);
			
			SwitchFirstAndLastCol(ch_down);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[2])[b][0] = (*ch_TLDR[3])[2][b];
			}
			SwitchFirstAndLastCol(ch_down);
			
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[3])[2][b] = ch_T_temp[b];
			}
			
			turn_sound.play();
			++moves;
		}
		
		if(selected_row == 1)
		{
			SwitchFirstAndLastCol(ch_top);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[0])[b][selected_row] = (*ch_TLDR[1])[1][b];
			}
			SwitchFirstAndLastCol(ch_top);
			
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[1])[1][b] = (*ch_TLDR[2])[b][1];
			}
			
			SwitchFirstAndLastCol(ch_down);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[2])[b][1] = (*ch_TLDR[3])[1][b];
			}
			SwitchFirstAndLastCol(ch_down);
			
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[3])[1][b] = ch_T_temp[b];;
			}
			
			turn_sound.play();
			++moves;
		}
		
		if(selected_row == 2)
		{
			SwitchFirstAndLastCol(ch_top);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[0])[b][selected_row] = (*ch_TLDR[1])[2][b];
			}
			SwitchFirstAndLastCol(ch_top);
			
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[1])[2][b] = (*ch_TLDR[2])[b][2];
			}
			
			SwitchFirstAndLastCol(ch_down);
			for(int b = 0; b < 3; ++b){
				(*ch_TLDR[2])[b][2] = (*ch_TLDR[3])[0][b];
			}
			SwitchFirstAndLastCol(ch_down);
			
			for(int b = 0; b < 3; ++b){	
				(*ch_TLDR[3])[0][b] = ch_T_temp[b];
			}
			
			turn_sound.play();
			++moves;
		}	
	}
}

// Rotations Rubic's cube notation

void Game::U()
{	
	horizontal = true;
	selected_row = 0;
 	selected_plane = 5;
	direction = 'L';
}	

void Game::F()
{
	horizontal = true;
	selected_row = 2;
	selected_plane = 2;
	direction = 'R';
}

void Game::R()
{
	horizontal = false;
	selected_col = 2;
	selected_plane = 5;
	direction = 'U';
}

void Game::L()
{
	horizontal = false;
	selected_col = 0;
	selected_plane = 5;
	direction = 'D';
}


void Game::D()
{
	horizontal = true;
	selected_row = 2;
	selected_plane = 5;
	direction = 'R';
}

void Game::B()
{
	horizontal = true;
	selected_row = 0;
	selected_plane = 2;
	direction = 'L';
}

void Game::Uprime()
{
	 U();
	 direction = 'R';
}

void Game::Fprime()
{
	F();
	direction = 'L';
}

void Game::Rprime()
{
	R();
	direction = 'D';
}

void Game::Lprime()
{
	L();
	direction = 'U';
}

void Game::Dprime()
{
	D();
	direction = 'L';
}

void Game::Bprime()
{
	B();
	direction = 'R';
}