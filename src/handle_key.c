/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddame <maddame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:54:43 by maddame           #+#    #+#             */
/*   Updated: 2025/01/21 09:51:51 by maddame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player_1(t_data *d, int new_y, int new_x)
{
	char	*tmp;
	char	*s;

	s = ft_itoa(d->num_mov);
	tmp = s;
	s = ft_strjoin("Moves: ", tmp);
	(free(tmp), write(1, s, ft_strlen(s)));
	(write(1, "\n", 1), free(s));
	if (d->map[new_y][new_x] == 'E')
	{
		d->map[d->y][d->x] = '0';
		d->x = new_x;
		d->y = new_y;
		d->map[d->y][d->x] = 'A';
	}
	else
	{
		if (d->map[d->y][d->x] == 'A')
			d->map[d->y][d->x] = 'E';
		else
			d->map[d->y][d->x] = '0';
		d->x = new_x;
		d->y = new_y;
		d->map[d->y][d->x] = 'P';
	}
}

void	move_player(t_data *d, int new_y, int new_x)
{
	if (d->map[new_y][new_x] != '1')
	{
		d->num_mov++;
		if (d->map[new_y][new_x] == 'E' && d->coins == 0)
		{
			(write(1, GRN, 5), write(2, "Congratulations, you win!\n", 26), \
			write(1, RESET, 4));
			cleaning(d);
			exit(0);
		}
		else if (d->map[new_y][new_x] == 'D')
		{
			(write(1, MAG, 5), write(2, \
			"Game over! Don't give up, try again!\n", 37), write(1, RESET, 4));
			cleaning(d);
			exit(1);
		}
		else if (d->map[new_y][new_x] == 'C')
			d->coins--;
		move_player_1(d, new_y, new_x);
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

int	handle_key_press(int keycode, t_data *d)
{
	int		new_x;
	int		new_y;

	(assign_player_pos(d), new_x = d->x);
	new_y = d->y;
	if (keycode == ESC_KEY)
	{
		(write(1, RED, 5), write(2, "Ooops ESC pressed\n", 18), \
		write(1, RESET, 4));
		cleaning(d);
		exit(0);
	}
	else if ((keycode == LEFT_KEY || keycode == A))
		new_x--;
	else if ((keycode == UP_KEY || keycode == W))
		new_y--;
	else if ((keycode == RIGHT_KEY || keycode == D))
		new_x++;
	else if ((keycode == DOWN_KEY || keycode == S))
		new_y++;
	if (keycode == LEFT_KEY || keycode == A || keycode == UP_KEY || \
	keycode == W || keycode == RIGHT_KEY || keycode == D || \
	keycode == DOWN_KEY || keycode == S)
		move_player(d, new_y, new_x);
	return (0);
}

void	update_animation(t_data *d)
{
	if (d->frame_slower == 1000)
	{
		d->frame_slower = 0;
		if (d->frame == 2)
			d->frame = 0;
		d->frame++;
	}
	d->frame_slower++;
	put_img_to_map(d, d->map);
}
