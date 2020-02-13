#include "Menu.h"

//=============================================================================
// default constructor
//=============================================================================


Menu::Menu(Input* input)
	:
	input(input)
{
}

void Menu::update()
{
	float x_center_ = GAME_WIDTH / 2.0f;
	float y_center_ = GAME_HEIGHT / 2.0f;

	float menu_left_ = x_center_ - 300.0f / 2.0f;
	float menu_right_ = x_center_ + 300.0f / 2.0f;

	float menu_top_ = y_center_ - 300.0f / 2.0f;
	float menu_bottom_ = y_center_ + 300.0f / 2.0f;

	float mouse_x = input->getMouseX();
	float mouse_y = input->getMouseY();

	// button
	if (mouse_x > menu_left_&& mouse_x < menu_right_) {
		// check first button
		if (mouse_y > menu_top_&& mouse_y < menu_bottom_ - 200.0f) {
			if (input->getMouseLButton()) {
				// do button 1 stuff
				OutputDebugString("Button 1 Pressed\n");
			}
		}
		// check second button
		if (mouse_y > (menu_top_ + 100.0f) && mouse_y < (menu_bottom_ - 100.0f)) {
			if (input->getMouseLButton()) {
				// do button 2 stuff			
				OutputDebugString("Button 2 Pressed\n");
			}
		}
		// check third button
		if (mouse_y > (menu_top_ + 200.0f) && mouse_y < menu_bottom_) {
			if (input->getMouseLButton()) {
				// do button 3 stuff
				//OutputDebugString("Button 3 Pressed\n");
				PostQuitMessage(0);
			}
		}
	}
}