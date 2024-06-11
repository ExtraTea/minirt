#ifndef LIGHT_H
# define LIGHT_H

# include "minirt.h"

typedef struct s_light	t_loght;

typedef struct s_reflection
{
	double	ambient_ratio;
	double	diffuse_ratio;
	double	specular_ratio;
	double	shininess;
}	t_reflection;

typedef struct s_ambient
{
	double	ratio;
	t_rgb	color;
}	t_ambient;

typedef struct s_light
{
	t_vec3			pos;
	double			ratio;
	t_rgb			color;
	struct s_light	*next;
}	t_light;

#endif