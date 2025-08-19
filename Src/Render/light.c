
#include "../../Inc/cube3d.h"

unsigned int dim_color(unsigned int color, double factor)
{
	// Extract red, green, blue from the color integer
	unsigned char r = (color >> 16) & 0xFF;	// Get red
	unsigned char g = (color >> 8) & 0xFF; 	// Get green
	unsigned char b = color & 0xFF;			// Get blue

	// Dim each channel
	r = (unsigned char)(r * factor);
	g = (unsigned char)(g * factor);
	b = (unsigned char)(b * factor);

	// Combine back to integer
	return (r << 16) | (g << 8) | b;
}