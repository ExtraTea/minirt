#ifndef MINIRT_H
# define MINIRT_H

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../libft/libft.h"
#include <limits.h>
#include <float.h>

#include "vector.h"
#include "object.h"
#include "light.h"
#include "camera.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WIDTH 480
# define HEIGHT 360

#define EPSILON 1e-6
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

t_environment	*make_env(char *str);
void	free_env(t_environment *env);
void	print_env(t_environment *env);
t_sqmatrix3 vec3_get_rotation_matrix(t_environment *env);

void	*ft_mlx_struct_init(void **mlx, t_data_img *img);
int handle_close(void *param);
int handle_keypress(int keycode, void *param);
void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color);
double is_collide_sphere(t_vec3 cam_pos, t_vec3 ray, t_sphere *sphere, t_vec3 *norm);
double is_collide_plane(t_vec3 cam_pos, t_vec3 ray, t_plane* plane, t_vec3 *norm);

int	rgb2hex(t_rgb color);
t_rgb	get_ambient_color(t_ambient *ambient, t_obj *obj);
int	can_reach_the_light(t_vec3 pos, t_vec3 ray,
		t_vec3 light_pos, t_environment *env);
t_rgb	assign_color(int a, int b, int c);
int get_color4ray(t_vec3 ray, t_environment *env);
double	is_collide_obj2(t_vec3 ray, t_vec3 pos, t_obj *now, t_vec3 *norm);
double	is_collide_obj(t_vec3 ray, t_environment *env, t_obj *now, t_vec3 *norm);

#endif