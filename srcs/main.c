#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"

#include "../include/minirt.h"
#include "../include/camera.h"
void	loop_something(t_mlx_data *data, t_environment env);
int main(void)
{
	t_mlx_data	mlx_data;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, WIDTH, HEIGHT, "micro-rt");
	mlx_data.img.img = mlx_new_image(mlx_data.mlx, (int)WIDTH, (int)HEIGHT);
	mlx_data.img.addr = mlx_get_data_addr(mlx_data.img.img, &mlx_data.img.bits_per_pixel,
			&mlx_data.img.line_length, &mlx_data.img.endian);

	t_environment env;
	env.ambient.ratio = 1.0f;
	env.ambient.color.r = 255;
	env.ambient.color.g = 255;
	env.ambient.color.b = 255;

	env.cam.fov = 120;
	env.cam.ori.x = 0;
	env.cam.ori.y = -0.0f;
	env.cam.ori.z = 1.0f;
	env.cam.pos.x = 0;
	env.cam.pos.y = 1.0f;
	env.cam.pos.z = 0; 

	env.light.color.r = 255;
	env.light.color.g = 255;
	env.light.color.b = 255;
	env.light.pos.x = 0;
	env.light.pos.y = 10;
	env.light.pos.z = 0;
	env.light.ratio = 1.0;

	t_plane plane;
	plane.color.r = 0;
	plane.color.g = 128;
	plane.color.b = 0;
	plane.point.x = 0;
	plane.point.y = 0;
	plane.point.z = 0;
	plane.norm.x = 0;
	plane.norm.y = 1.0f;
	plane.norm.z = 0;

	t_sphere sphere;
	sphere.center.x = 0;
	sphere.center.y = 2.0f;
	sphere.center.z = 3.0f;
	sphere.color.r = 128;
	sphere.color.g = 0;
	sphere.color.b = 0;
	sphere.r = 1.5f;

	env.obj = (t_obj *)malloc(sizeof (t_obj));
	env.obj->obj = &plane;
	env.obj->type = 'p';
	env.obj->next = (t_obj *)malloc(sizeof (t_obj));
	env.obj->next->obj = &sphere;
	env.obj->next->type = 's';
	env.obj->next->next = NULL;
	
	loop_something(&mlx_data, env);
	mlx_loop(mlx_data.mlx);

}

void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double is_collide_sphere(t_camera cam, t_vec3 ray, t_sphere *sphere){
	double a = vec3_dot(ray, ray);
	double b = 2 * (vec3_dot(cam.pos, ray) - vec3_dot(ray, sphere->center));
	double c = -2 * vec3_dot(cam.pos, sphere->center) + vec3_dot(sphere->center, sphere->center) + vec3_dot(cam.pos, cam.pos) - sphere->r * sphere->r;
	double t;

	if (b * b - 4 * a * c >= 0){
		t = (-b - sqrt(b * b - 4 * a * c)) / 2 * a;
		if (t <= 0){
			t = (-b + sqrt(b * b - 4 * a * c)) / 2 * a;
			if (t <= 0){
				return (-1.0f);
			}
			else{
				return (t);
			}
		}
		else{
			return (t);
		}
	}
	else{
		return (-1.0f);
	}
}

double is_collide_plane(t_camera cam, t_vec3 ray, t_plane* plane){
	double t;

	t = (vec3_dot(vec3_sub(plane->point, cam.pos), plane->norm) / vec3_dot(ray, plane->norm));
	if (t > 0) //衝突
		return (t);
	else
		return (-1.0f);
}

int	rgb2hex(t_rgb color){
	return (color.r * 256 * 256 + color.g * 256 + color.b);
}

t_rgb get_ambient_color(t_ambient ambient, t_obj *obj){
	t_rgb ret;

	if (obj->type == 'p')
		ret = ((t_plane *)(obj->obj))->color;
	else if (obj->type == 's')
		ret = ((t_sphere *)(obj->obj))->color;
	ret.r = ambient.color.r * ambient.ratio * ret.r / 255;
	ret.g = ambient.color.g * ambient.ratio * ret.g / 255;
	ret.b = ambient.color.b * ambient.ratio * ret.b / 255;

	return (ret);
}

t_rgb get_diffuse_color(t_vec3 ray, t_environment env){
	t_rgb ret;

	
}

double is_collide_obj(t_vec3 ray, t_environment env, t_obj *now){
	if (now->type == 'p')
		return (is_collide_plane(env.cam, ray, (t_plane *)(now->obj)));
	if (now->type == 's')
		return (is_collide_sphere(env.cam, ray, (t_sphere *)(now->obj)));
}

int get_color4ray(t_vec3 ray, t_environment env){
	double min;
	double t;
	int color;
	t_obj *now;

	min = DBL_MAX;
	now = env.obj;
	while (now != NULL){
		t = is_collide_obj(ray, env, now);
		if (t > 0 && t < min){
			min = t;
			color = rgb2hex(get_ambient_color(env.ambient, now));
		}
		now = now->next;
	}
	if (min == DBL_MAX){
		color = 0xFF;
	}

	return (color);
}

void	loop_something(t_mlx_data *data, t_environment env){
	double fov_d = (double)env.cam.fov * M_PI / 180.0f;
	int color;

	t_vec3 y_axis;
	y_axis.x = 0;
	y_axis.y = 1;
	y_axis.z = 0;
	t_vec3 neo_x = vec3_cross(env.cam.ori, y_axis);
	t_vec3 neo_y = vec3_cross(neo_x, env.cam.ori);
	t_sqmatrix3 rotation_matrix = vec3_get_rotation_matrix(neo_x, neo_y, env.cam.ori);
	int i = 0;
	while (i < HEIGHT){
		int j = 0;
		while (j < WIDTH){
			t_vec3 ray;
			ray.x = 2 * tan(fov_d/2) / (double)WIDTH * (double)(j - WIDTH/2);
			ray.y = 2 * tan(fov_d/2) / (double)WIDTH * (double)(i - WIDTH/2);
			ray.z = 1;
			ray = rotate_matrix(rotation_matrix, ray);
			color = get_color4ray(ray, env);
			my_mlx_pixel_put(&data->img, j, HEIGHT - 1 - i, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	mlx_loop(data->mlx);
}
