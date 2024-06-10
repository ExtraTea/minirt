#ifndef MINIRT_H
# define MINIRT_H

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../libft/libft.h"

#include "vector.h"
#include "object.h"
#include "light.h"
#include "camera.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WIDTH 500
# define HEIGHT 500

typedef struct s_data_img{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img;

typedef struct s_mlx_data{
	void		*mlx;
	void		*mlx_win;
	t_data_img	img;
}	t_mlx_data;

typedef struct s_obj{
	char type; // s for sphere, p for plane, c for cylinder;
	void *obj;
	struct s_obj *next;
}t_obj;

typedef struct	s_environment
{
	t_ambient	*ambient;
	t_light		*light;
	t_camera	*cam;
	t_obj		*obj;
}	t_environment;

#endif