#ifndef CAMERA_H
# define CAMERA_H

# include "minirt.h"
# include "vector.h"

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	ori;
	int		fov;
}	t_camera;

#endif
