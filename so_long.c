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
int		check_map(t_data *d)
{
	int		x;
	int		y;

	y = -1;
	while (++y >= 0 && y < d->map_height)
	{
		x = -1;
		while (++x >= 0 && x < d->map_width)
		{
			if (d->map[y][0] != '1' || d->map[y][d->map_width - 1] != '1' || d->map[0][0] != '1' || d->map[0][x] != '1' || d->map[d->map_height - 1][0] != '1' || d->map[d->map_height - 1][x] != '1')
				return (0);
			if (d->map[y][x] == '1')
				d->walls++;
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
		}
	}
	return (!(d->exit_E != 1 || d->st_pos != 1 || d->collectibles < 1 || d->free_space < 1 || d->walls < ((d->map_height * 2) + (d->map_width * 2) - 4)));
}

void	dfs(char **map, int y, int x, char O, char N, t_data *d)
{
	int		r;
	int		c;

	if (O == N)
		return ;
	r = d->map_height;
	c = d->map_width;
	// printf("y = %d\tx = %d\tr = %d\tc = %d\to = %c\tn = %c\tmap = %c", y, x, r, c, O, N, map[y][x]);
	if (y < 0 || y >= r || x < 0 || x >= c || map[y][x] == N || map[y][x] == '1')
		return ;
	else
	{
		map[y][x] = N;
		dfs(map, y + 1, x, O, N, d);
		dfs(map, y - 1, x, O, N, d);
		dfs(map, y, x + 1, O, N, d);
		dfs(map, y, x - 1, O, N, d);
	}
}

char	**map_cpy(char **map, int y, int x)
{
	int		i;
	int		j;
	char	**new_map;

	new_map = malloc(sizeof(char *) * (y + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < y)
	{
		new_map[i] = malloc(sizeof(char) * (x + 1));
		if (!new_map[i])
			return (NULL);
		j = 0;
		while (j < x)
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

void	free_map(char **pt, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		free(pt[i]);
		i++;
	}
	free(pt);
}

int		valid_map(t_data *d, char **map)
{
	int		y;
	int		x;
	int		c;
	char	**cp_map;

	cp_map = map_cpy(map, d->map_height, d->map_width);
	dfs(cp_map, 1, 1, '0', 'N', d);
	c = 0;
	y = 0;
	while (y < d->map_height)
	{
		x = 0;
		while (x < d->map_width)
		{
			if (cp_map[y][x] == 'C' || cp_map[y][x] == 'E' || cp_map[y][x] == '0')
				c++;
			printf("%c", cp_map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	free_map(cp_map, d->map_height);
	return (c == 0);
}

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
