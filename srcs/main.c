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
	env.ambient.ratio = 0.6f;
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
	env.light.pos.x = -3.0f;
	env.light.pos.y = 3.0f;
	env.light.pos.z = -3.0f;
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

double is_collide_sphere(t_vec3 cam_pos, t_vec3 ray, t_sphere *sphere, t_vec3 *norm){
	double a = vec3_dot(ray, ray);
	double b = 2 * (vec3_dot(cam_pos, ray) - vec3_dot(ray, sphere->center));
	double c = -2 * vec3_dot(cam_pos, sphere->center) + vec3_dot(sphere->center, sphere->center) + vec3_dot(cam_pos, cam_pos) - sphere->r * sphere->r;
	double t;

	if (b * b - 4 * a * c >= 0){
		t = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (t <= 0){
			t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
			if (t <= 0){
				return (-1.0f);
			}
			else{
				*norm = vec3_normalize(vec3_sub(vec3_sum(cam_pos, vec3_mul(ray, t)), sphere->center));
				return (t);
			}
		}
		else{
			*norm = vec3_normalize(vec3_sub(vec3_sum(cam_pos, vec3_mul(ray, t)), sphere->center));
			return (t);
		}
	}
	else{
		return (-1.0f);
	}
}

double is_collide_plane(t_vec3 cam_pos, t_vec3 ray, t_plane* plane, t_vec3 *norm){
	double t;

	t = (vec3_dot(vec3_sub(plane->point, cam_pos), plane->norm) / vec3_dot(ray, plane->norm));
	norm->x = plane->norm.x;
	norm->y = plane->norm.y;
	norm->z = plane->norm.z; 
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
	ret.r = (int)((double)ambient.color.r * ambient.ratio * (double)ret.r / 255.0f);
	ret.g = (int)((double)ambient.color.g * ambient.ratio * (double)ret.g / 255.0f);
	ret.b = (int)((double)ambient.color.b * ambient.ratio * (double)ret.b / 255.0f);
	return (ret);
}

int can_reach_the_light(t_vec3 pos, t_vec3 ray, t_vec3 light_pos){
	return (1);
}

t_rgb get_diffuse_color(t_vec3 ray, t_environment env, double t, t_vec3 norm, t_obj *obj){
	t_rgb ret;
	t_vec3 point = vec3_sum(vec3_mul(ray, t), env.cam.pos);

	if (vec3_dot(vec3_sub(env.light.pos, point), norm) <= 0){
		ret.r = 0;
		ret.g = 0;
		ret.b = 0;
		return (ret);
	}
	if (obj->type == 'p')
		ret = ((t_plane *)(obj->obj))->color;
	else if (obj->type == 's')
		ret = ((t_sphere *)(obj->obj))->color;
	if (can_reach_the_light(point, vec3_sub(env.light.pos, point), env.light.pos) == 1){
		ret.r = (int)((double)env.light.color.r * env.light.ratio * (double)ret.r / 255.0f * vec3_dot(vec3_normalize(norm), vec3_normalize(vec3_sub(env.light.pos, point))));
		ret.g = (int)((double)env.light.color.g * env.light.ratio * (double)ret.g / 255.0f * vec3_dot(vec3_normalize(norm), vec3_normalize(vec3_sub(env.light.pos, point))));
		ret.b = (int)((double)env.light.color.b * env.light.ratio * (double)ret.b / 255.0f * vec3_dot(vec3_normalize(norm), vec3_normalize(vec3_sub(env.light.pos, point))));
		return (ret);
	}
	else{
		ret.r = 0;
		ret.g = 0;
		ret.b = 0;
		return (ret);
	}
}

t_rgb get_full_color(t_vec3 ray, t_environment env, double t, t_vec3 norm, t_obj *obj){
	t_rgb a = get_ambient_color(env.ambient, obj);
	t_rgb b = get_diffuse_color(ray, env, t, norm, obj);

	a.r += b.r;
	a.g += b.g;
	a.b += b.b;

	return (a);
}

double is_collide_obj(t_vec3 ray, t_environment env, t_obj *now, t_vec3 *norm){
	if (now->type == 'p')
		return (is_collide_plane(env.cam.pos, ray, (t_plane *)(now->obj), norm));
	if (now->type == 's')
		return (is_collide_sphere(env.cam.pos, ray, (t_sphere *)(now->obj), norm));
}

int get_color4ray(t_vec3 ray, t_environment env){
	double min;
	double t;
	int color;
	t_obj *now;
	t_vec3 norm;

	min = DBL_MAX;
	now = env.obj;
	while (now != NULL){
		t = is_collide_obj(ray, env, now, &norm);
		if (t > 0 && t < min){
			min = t;
			color = rgb2hex(get_full_color(ray, env, t, norm, now));
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
}
