#include "../../include/read.h"

bool	check_01(double num)
{
	if (0 <= num && num <= 1)
		return (true);
	return (false);
}

bool	check_coler(t_rgb rgb)
{
	if (rgb.b == COLER_ERROR || rgb.g == COLER_ERROR || rgb.r == COLER_ERROR)
		return (false);
	return (true);
}

bool	check_norm(t_vec3 vet3)
{
	if (1 < vet3.x || vet3.x < -1)
		return (false);
	if (1 < vet3.y || vet3.y < -1)
		return (false);
	if (1 < vet3.z || vet3.z < -1)
		return (false);
	return (true);
}

bool	check_fov(double num)
{
	if (num == FOV_ERROR)
		return (false);
	return (true);
}
