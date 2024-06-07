#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"

#include "../include/minirt.h"
#include "../include/camera.h"
void	loop_something(t_camera cam, t_mlx_data *data, t_plane plane);

int main(void)
{
	t_mlx_data	mlx_data;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, WIDTH, HEIGHT, "micro-rt");
	mlx_data.img.img = mlx_new_image(mlx_data.mlx, (int)WIDTH, (int)HEIGHT);
	mlx_data.img.addr = mlx_get_data_addr(mlx_data.img.img, &mlx_data.img.bits_per_pixel,
			&mlx_data.img.line_length, &mlx_data.img.endian);

	t_camera cam;
	cam.fov = 120;
	cam.ori.x = 0;
	cam.ori.y = -0.0f;
	cam.ori.z = 1.0f;
	cam.pos.x = 0;
	cam.pos.y = 100.0f;
	cam.pos.z = 0;

	t_plane plane;
	plane.color.r = 128;
	plane.color.g = 128;
	plane.color.b = 128;
	plane.point.x = 0;
	plane.point.y = 0;
	plane.point.z = 0;
	plane.norm.x = 0;
	plane.norm.y = 1.0f;
	plane.norm.z = 0;

	// t_sphere sphere;
	// sphere.center.x = 0;
	// sphere.center.y = 2.0f;
	// sphere.center.z = 2.0f;
	// sphere.color.r = 128;
	// sphere.color.g = 128;
	// sphere.color.b = 128;
	
	loop_something(cam, &mlx_data, plane);
	mlx_loop(mlx_data.mlx);

}

void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}



void	loop_something(t_camera cam, t_mlx_data *data, t_plane plane){
	double fov_d = (double)cam.fov * M_PI / 180.0f;
	t_vec3 ray_ori;
	t_vec3 y_axis;
	y_axis.x = 0;
	y_axis.y = 1;
	y_axis.z = 0;
	t_vec3 neo_x = vec3_cross(cam.ori, y_axis);
	t_vec3 neo_y = vec3_cross(neo_x, cam.ori);
	t_sqmatrix3 rotation_matrix = vec3_get_rotation_matrix(neo_x, neo_y, cam.ori);
	int i = 0;
	while (i < HEIGHT){
		int j = 0;
		while (j < WIDTH){
			t_vec3 ray;
			ray.x = 2 * tan(fov_d/2) / (double)WIDTH * (double)(j - WIDTH/2);
			ray.y = 2 * tan(fov_d/2) / (double)WIDTH * (double)(i - WIDTH/2);
			ray.z = 1;
			ray = rotate_matrix(rotation_matrix, ray);
			if ((vec3_dot(vec3_sub(plane.point, cam.pos), plane.norm) / vec3_dot(ray, plane.norm)) > 0) //衝突
				my_mlx_pixel_put(&data->img, j, HEIGHT - 1 - i, 0x000000FF); //青
			else
				my_mlx_pixel_put(&data->img, j, HEIGHT - 1 - i, 0x0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	mlx_loop(data->mlx);
}
