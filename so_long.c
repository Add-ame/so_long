#include "so_long.h"
#include <stdio.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;
	int		i;
	int		j;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	// mlx_hook(vars.win, 12, 0, resized, NULL);
	// mlx_hook(vars.win, 7, 0, EnterNotify, &vars);
	// mlx_hook(vars.win, 8, 0, LeaveNotify, &vars);
	// mlx_hook(vars.win, 5, 1L<<0, up, &vars);
	// img_ptr = mlx_xpm_file_to_image(vars.mlx, "path/to/image.xpm", &img_width, &img_height);

	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (j = 0; j < 1080; j++)
	{
		i = -1;
		while (++i < 1920)
			my_mlx_pixel_put(&img, i, j, 0x00FF0000);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
}
