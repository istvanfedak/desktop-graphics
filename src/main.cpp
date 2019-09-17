#include "library.h"

int main()
{
	make_window(2000, 1000);
	set_pen_color(color::light_blue);
	start_shape();
	move_to(200, 900);
	note_position();
	move_to(1000, 600);
	note_position();
	move_to(1800, 900);
	note_position();
	move_to(1000, 100);
	note_position();
	draw_shape();
	draw();
	return 0;
}
