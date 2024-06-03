#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"

int event_handler(int key, void *mlx)
{
 printf("called\n");
 return (0);
}

int main(void)
{
 void *mlx;
 void *mlx_win;

 mlx = mlx_init();
 mlx_win = mlx_new_window(mlx, 300, 300, "Hello World");
 mlx_hook(mlx_win, KeyPress, KeyPressMask, event_handler, mlx);
 mlx_loop(mlx);
}