#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "light.h"

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	norm;
	t_rgb	color;
}	t_plane;

typedef struct s_sphere
{
	t_vec3	center;
	double	r;
	t_rgb	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	diameter;
	double	height;
	t_rgb	color;
}	t_cylinder;

#endif