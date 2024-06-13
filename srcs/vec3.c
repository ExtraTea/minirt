#include "../include/minirt.h"

double	vec_len(t_vec3 a)
{
	return (sqrt(vec3_dot(a, a)));
}
