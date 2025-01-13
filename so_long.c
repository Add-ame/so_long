#include "so_long.h"

int		handle_key_press(int keycode, t_data *d)
{
	int		new_x;
	int		new_y;

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
	return (0);
}

char	**take_map(t_data *d)
{
	char	*s;
	char	**map;
	int		fd;
	int		i;
	int		j;

	fd = open("map.ber", O_RDONLY);
	d->map_height = 1;
	s = get_next_line(fd);
	while (s)
	{
		i = 0;
		d->map_width = 0;
		while (s[i])
		{
			if (s[i] == '\n')
				d->map_height++;
			else
				d->map_width++;
			i++;
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	map = malloc(sizeof(char *) * (d->map_height + 1));
	if (!map)
		return (NULL);
	fd = open("map.ber", O_RDONLY);
	i = 0;
	s = get_next_line(fd);
	while (i < d->map_height)
	{
		map[i] = malloc(sizeof(char) * (d->map_width + 1));
		if (!map[i])
			return (NULL);
		j = 0;
		while (j < d->map_width)
		{
			if (s[j] == 'C')
				d->coins++;
			map[i][j] = s[j];
			j++;
		}
		map[i][j] = '\0';
		free(s);
		s = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
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
			// printf("%c", c);
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
		// printf("\n");
		i++;
	}
}

/*
1- take the map
2- load the images
3- put every img to it's place in the map
4- handle input
*/
int		main()
{
	t_data	d;
	char	**map;
	int		x;
	int		y;

	if (!check_map(&d))
		return (0);
	d.num_mov = 0;
	d.coins = 0;
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, 9 * 32, 5 * 32, "Titleeeee");

	map = take_map(&d);
	if (!map)
		return (0);

	load_imgs(&d);

	put_img_to_map(&d, map);

	for (y = 0; y < d.map_height; y++)
	{
		for (x = 0; x < d.map_width; x++)
		{
			if (map[y][x] == 'P')
			{
				d.x = x;
				d.y = y;
				break ;
			}
		}
	}
	d.map = map;
	mlx_hook(d.win, 2, 1L<<0, handle_key_press, &d);
	mlx_loop(d.mlx);
}
