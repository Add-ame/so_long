#include "so_long.h"

void	init_null(t_data *d)
{
	int		i;

	d->win = NULL;
	d->mlx = NULL;
	d->background.img = NULL;
	d->wall.img = NULL;
	d->coin.img = NULL;
	d->exit_2.img = NULL;
	d->exitt.img = NULL;
	d->enemy.img = NULL;
	d->map = NULL;
	i = 0;
	while (i < 9)
	{
		d->player[i].img = NULL;
		i++;
	}
}

void	initialize(t_data *d)
{
	d->x = 0;
	d->y = 0;
	d->j = 0;
	d->i = 0;
	d->player_p = 0;
	d->num_mov = 0;
	d->coins = 0;
	d->walls = 0;
	d->collectibles = 0;
	d->st_pos = 0;
	d->exit_e = 0;
	d->free_space = 0;
	d->frame = 0;
	d->n = 'N';
	d->o = '0';
	init_null(d);
}

void	cleaning_player(t_data *d)
{
	int		i;

	i = 0;
	while (i < 9)
	{
		if (d->player[i].img)
			mlx_destroy_image(d->mlx, d->player[i].img);
		i++;
	}
}

void	cleaning(t_data *d)
{
	if (d->map)
		free_map(d->map, d->map_height);
	if (d->background.img)
		mlx_destroy_image(d->mlx, d->background.img);
	if (d->wall.img)
		mlx_destroy_image(d->mlx, d->wall.img);
	if (d->coin.img)
		mlx_destroy_image(d->mlx, d->coin.img);
	if (d->enemy.img)
		mlx_destroy_image(d->mlx, d->enemy.img);
	if (d->exit_2.img)
		mlx_destroy_image(d->mlx, d->exit_2.img);
	if (d->exitt.img)
		mlx_destroy_image(d->mlx, d->exitt.img);
	cleaning_player(d);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
}

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2)
		return (0);
	initialize(&d);
	d.map = take_map(&d, av);
	if (!d.map)
		return (0);
	if (!check_map(&d) || !valid_map(&d, d.map) || !valid_map_2(&d, d.map))
	{
		(cleaning(&d), write(2, "Error\n", 6));
		exit(1);
	}
	d.mlx = mlx_init();
	if (!d.mlx)
		return (0);
	d.win = mlx_new_window(d.mlx, d.map_width * 32, \
	d.map_height * 32, "Titleeeee");
	if (!d.win)
		return (0);
	load_imgs(&d);
	put_img_to_map(&d, d.map);
	mlx_hook(d.win, 2, 1L << 0, handle_key_press, &d);
	mlx_loop_hook(d.mlx, (int (*)())update_animation, &d);
	(mlx_hook(d.win, 17, 0, close_win, &d), mlx_loop(d.mlx));
}
