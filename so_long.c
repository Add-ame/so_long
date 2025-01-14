#include "so_long.h"



void	move_player(t_data *d, int new_y, int new_x)
{
	if (d->map[new_y][new_x] == 'E' && d->coins != 0)
		d->num_mov++;
	else if (d->map[new_y][new_x] != '1')
	{
		if (d->map[new_y][new_x] == 'E' && d->coins == 0)
		{
			mlx_destroy_window(d->mlx, d->win);
			exit(0);
		}
		else if (d->map[new_y][new_x] == 'C')
			d->coins--;
		d->map[d->y][d->x] = '0';
		d->x = new_x;
		d->y = new_y;
		d->map[d->y][d->x] = 'P';
		put_img_to_map(d, d->map);
	}
}

void	assign_player_pos(t_data *d)
{
	int		x;
	int		y;

	y = 0;
	while (y < d->map_height)
	{
		x = 0;
		while (x < d->map_width)
		{
			if (d->map[y][x] == 'P')
			{
				d->x = x;
				d->y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}

int		handle_key_press(int keycode, t_data *d)
{
	int		new_x;
	int		new_y;

	assign_player_pos(d);
	new_x = d->x;
	new_y = d->y;
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	else if ((keycode == 65361 || keycode == 97) && ++d->num_mov && printf("%d ", d->num_mov))//A
		new_x--;
	else if ((keycode == 65362 || keycode == 119) && ++d->num_mov && printf("%d ", d->num_mov))//W
		new_y--;
	else if ((keycode == 65363 || keycode == 100) && ++d->num_mov && printf("%d ", d->num_mov))//D
		new_x++;
	else if ((keycode == 65364 || keycode == 115) && ++d->num_mov && printf("%d ", d->num_mov))//S
		new_y++;
	move_player(d, new_y, new_x);
	return (0);
}

void	load_imgs(t_data *d)
{
	d->background.img = mlx_xpm_file_to_image(d->mlx, "back.xpm", &d->background.width, &d->background.height);
	// mlx_put_image_to_window(d->mlx, d->win, d->background.img, 0, 0);
	d->player.img = mlx_xpm_file_to_image(d->mlx, "player.xpm", &d->coin.width, &d->background.height);
	// mlx_put_image_to_window(d->mlx, d->win, d->player.img, 20, 0);
	d->coin.img = mlx_xpm_file_to_image(d->mlx, "coin.xpm", &d->coin.width, &d->coin.height);
	// mlx_put_image_to_window(d->mlx, d->win, d->coin.img, 50, 0);
	d->exitt.img = mlx_xpm_file_to_image(d->mlx, "exit.xpm", &d->exitt.width, &d->exitt.height);
	d->wall.img = mlx_xpm_file_to_image(d->mlx, "wall.xpm", &d->wall.width, &d->wall.height);
	// mlx_put_image_to_window(d->mlx, d->win, d->exitt.img, 60, 0);
}

void	put_img_to_map(t_data *d, char **map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < d->map_height)
	{
		j = 0;
		while (j < d->map_width)
		{
			c = map[i][j];
			if (c == '0')
				mlx_put_image_to_window(d->mlx, d->win, d->background.img, j * 32, i * 32);
			else if (c == '1')
				mlx_put_image_to_window(d->mlx, d->win, d->wall.img, j * 32, i * 32);
			else if (c == 'P')
				mlx_put_image_to_window(d->mlx, d->win, d->player.img, j * 32, i * 32);
			else if (c == 'C')
				mlx_put_image_to_window(d->mlx, d->win, d->coin.img, j * 32, i * 32);
			else if (c == 'E')
				mlx_put_image_to_window(d->mlx, d->win, d->exitt.img, j * 32, i * 32);
			j++;
		}
		i++;
	}
}

/*
1- check if the map has: walls, collectibles, free spaces.
	and 1 E, 1 C, 1 P
2- 
*/

/*
1- take the map
2- load the images
3- put every img to it's place in the map
4- handle input
5- check map
4- check if the playyer can eat all collectibles
*/
int		main(int ac, char **av)
{
	t_data	d;

	if (ac != 2)
		return (0);
	initialize(&d);
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, 9 * 32, 5 * 32, "Titleeeee");
	d.map = take_map(&d, av);
	if (!d.map)
		return (0);
	if (!check_map(&d) || !valid_map(&d, d.map))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	load_imgs(&d);
	put_img_to_map(&d, d.map);
	mlx_hook(d.win, 2, 1L<<0, handle_key_press, &d);
	mlx_loop(d.mlx);
}
