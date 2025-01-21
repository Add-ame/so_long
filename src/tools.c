/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddame <maddame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:55:03 by maddame           #+#    #+#             */
/*   Updated: 2025/01/21 09:52:14 by maddame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_player(t_data *d)
{
	d->player[0].img = mlx_xpm_file_to_image(d->mlx, "textures/player_1.xpm", \
	&d->player[0].width, &d->player[0].height);
	d->player[1].img = mlx_xpm_file_to_image(d->mlx, "textures/player_2.xpm", \
	&d->player[1].width, &d->player[1].height);
	d->player[2].img = mlx_xpm_file_to_image(d->mlx, "textures/player_3.xpm", \
	&d->player[2].width, &d->player[2].height);
	d->player[3].img = mlx_xpm_file_to_image(d->mlx, "textures/player_4.xpm", \
	&d->player[3].width, &d->player[3].height);
	d->player[4].img = mlx_xpm_file_to_image(d->mlx, "textures/player_5.xpm", \
	&d->player[4].width, &d->player[4].height);
	d->player[5].img = mlx_xpm_file_to_image(d->mlx, "textures/player_6.xpm", \
	&d->player[5].width, &d->player[5].height);
	d->player[6].img = mlx_xpm_file_to_image(d->mlx, "textures/player_7.xpm", \
	&d->player[6].width, &d->player[6].height);
	d->player[7].img = mlx_xpm_file_to_image(d->mlx, "textures/player_8.xpm", \
	&d->player[7].width, &d->player[7].height);
	d->player[8].img = mlx_xpm_file_to_image(d->mlx, "textures/player_9.xpm", \
	&d->player[8].width, &d->player[8].height);
}

void	load_imgs(t_data *d)
{
	load_player(d);
	d->background.img = mlx_xpm_file_to_image(d->mlx, "textures/back.xpm", \
	&d->background.width, &d->background.height);
	d->coin.img = mlx_xpm_file_to_image(d->mlx, "textures/coin.xpm", \
	&d->coin.width, &d->coin.height);
	d->exitt.img = mlx_xpm_file_to_image(d->mlx, "textures/exit.xpm", \
	&d->exitt.width, &d->exitt.height);
	d->wall.img = mlx_xpm_file_to_image(d->mlx, "textures/wall.xpm", \
	&d->wall.width, &d->wall.height);
	d->exit_2.img = mlx_xpm_file_to_image(d->mlx, "textures/exit_2.xpm", \
	&d->exit_2.width, &d->exit_2.height);
	d->enemy.img = mlx_xpm_file_to_image(d->mlx, "textures/enemy.xpm", \
	&d->enemy.width, &d->enemy.height);
	d->player_exit.img = mlx_xpm_file_to_image(d->mlx, \
	"textures/player_exit.xpm", &d->player_exit.width, &d->player_exit.height);
}

void	put_img_to_map(t_data *d, char **map)
{
	char	*s;
	char	*tmp;

	d->i = -1;
	while (++d->i >= 0 && d->i < d->map_height)
	{
		d->j = -1;
		while (++d->j >= 0 && d->j < d->map_width)
		{
			d->c = map[d->i][d->j];
			puting(d);
		}
	}
	s = ft_itoa(d->num_mov);
	tmp = s;
	s = ft_strjoin("Moves: ", tmp);
	free(tmp);
	mlx_string_put(d->mlx, d->win, 10, 20, 0xFFFFFF, s);
	free(s);
}

void	keep_puting(t_data *d)
{
	if (d->c == 'E')
	{
		if (d->coins == 0)
			mlx_put_image_to_window(d->mlx, d->win, d->exit_2.img, \
			d->j * 32, d->i * 32);
		else
			mlx_put_image_to_window(d->mlx, d->win, d->exitt.img, \
			d->j * 32, d->i * 32);
	}
	else if (d->c == 'A')
		mlx_put_image_to_window(d->mlx, d->win, d->player_exit.img, \
			d->j * 32, d->i * 32);
}

void	puting(t_data *d)
{
	if (d->c == '0')
		mlx_put_image_to_window(d->mlx, d->win, d->background.img, \
		d->j * 32, d->i * 32);
	else if (d->c == '1')
		mlx_put_image_to_window(d->mlx, d->win, d->wall.img, \
		d->j * 32, d->i * 32);
	else if (d->c == 'P')
		mlx_put_image_to_window(d->mlx, d->win, d->player[d->frame].img, \
		d->j * 32, d->i * 32);
	else if (d->c == 'C')
		mlx_put_image_to_window(d->mlx, d->win, d->coin.img, \
		d->j * 32, d->i * 32);
	else if (d->c == 'D')
		mlx_put_image_to_window(d->mlx, d->win, d->enemy.img, \
		d->j * 32, d->i * 32);
	keep_puting(d);
}
