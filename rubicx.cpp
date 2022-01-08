#include "Game.h"

int main()
{
	Game g;
	while(g.window.isOpen()){
		
		if (!g.lost_focus) {
			g.HandleInput();
		}
		
		g.Update();	
		g.Render();
	}
}