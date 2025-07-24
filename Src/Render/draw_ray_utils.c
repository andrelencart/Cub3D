
#include "../../Inc/cube3d.h"

int	get_tile_color(char c)
{
	if (c == '1')
		return (CEILING_COLOR_DK_G);
	if (c == '0')
		return (FLOOR_COLOR_LGHT_G);
	if (c == 'P')
		return (RED);
	return (WHITE);
}