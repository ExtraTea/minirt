#include "../include/minirt.h"

int	handle_keypress(int keycode, void *param)
{
	if (keycode == 53)
		mlx_loop_end(param);
	return (0);
}

int	handle_close(void *param)
{
	mlx_loop_end(param);
	return (0);
}

void	*ft_mlx_struct_init(void **mlx, t_data_img *img)
{
	void	*mlx_win;

	*mlx = mlx_init();
	if (*mlx == NULL)
		return (NULL);
	mlx_win = mlx_new_window(*mlx, (int)WIDTH, (int)HEIGHT, "miniRT");
	if (mlx_win == NULL)
		return (NULL);
	img->img = mlx_new_image(*mlx, (int)WIDTH, (int)HEIGHT);
	if (img->img == NULL)
		return (NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (img->addr == NULL)
		return (NULL);
	return (mlx_win);
}

void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
