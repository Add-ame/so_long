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
1- check if the map has: walls, collectibles, free spaces.
	and 1 E, 1 C, 1 P
2- 
*/
int		check_map(t_data *d)
{
	int		x;
	int		y;

	d->walls = 0;
	d->collectibles = 0;
	d->st_pos = 0;
	d->exit_E = 0;
	d->free_space = 0;
	y = 0;
	while (y < d->map_height)
	{
		x = 0;
		while (x < d->map_width)
		{
			if (d->map[y][0] != '1' || d->map[y][d->map_width - 1] != '1' || d->map[0][0] != '1' || d->map[0][x] != '1' || d->map[d->map_height - 1][0] != '1' || d->map[d->map_height - 1][x] != '1')
				return (0);
			if (d->map[y][x] == '1')
			{
				// printf("y = %d\tx = %d\n", y, x);
				d->walls++;
			}
			else if (d->map[y][x] == 'P')
				d->st_pos++;
			else if (d->map[y][x] == 'C')
				d->collectibles++;
			else if (d->map[y][x] == 'E')
				d->exit_E++;
			else if (d->map[y][x] == '0')
				d->free_space++;
			else
				return (0);
			x++;
		}
		y++;
	}
	// printf("1 = %d\tP = %d\tE = %d\tC = %d\t0 = %d\n", d->walls, d->st_pos, d->exit_E, d->collectibles, d->free_space);
	// printf("%d\t%d\t%d\n", (d->map_height * 2), (d->map_width * 2), (d->map_height * 2) + (d->map_width * 2) - 4);
	if (d->exit_E != 1 || d->st_pos != 1 || d->collectibles < 1 || d->free_space < 1 || d->walls < ((d->map_height * 2) + (d->map_width * 2) - 4))
		return (0);
	return (1);
}

/*
1- take the map
2- load the images
3- put every img to it's place in the map
4- handle input
5- check map
*/
int		main()
{
	t_data	d;
	int		x;
	int		y;

	d.num_mov = 0;
	d.coins = 0;
	d.mlx = mlx_init();

	d.win = mlx_new_window(d.mlx, 9 * 32, 5 * 32, "Titleeeee");
	d.map = take_map(&d);
	if (!d.map)
		return (0);

	if (!check_map(&d))
	{
		printf("Error\n");
		return (0);
	}

	load_imgs(&d);

	put_img_to_map(&d, d.map);

	for (y = 0; y < d.map_height; y++)
	{
		for (x = 0; x < d.map_width; x++)
		{
			if (d.map[y][x] == 'P')
			{
				d.x = x;
				d.y = y;
				break ;
			}
		}
	}
	mlx_hook(d.win, 2, 1L<<0, handle_key_press, &d);
	mlx_loop(d.mlx);
}
