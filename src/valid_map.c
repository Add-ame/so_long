/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddame <maddame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:55:09 by maddame           #+#    #+#             */
/*   Updated: 2025/01/21 09:55:15 by maddame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	dfs(char **map, int y, int x, t_data *d)
{
	int		r;
	int		c;

	if (d->o == d->n)
		return ;
	r = d->map_height;
	c = d->map_width;
	if (y < 0 || y >= r || x < 0 || x >= c || map[y][x] == d->n \
		|| map[y][x] == '1' || map[y][x] == 'D')
		return ;
	else
	{
		map[y][x] = d->n;
		dfs(map, y + 1, x, d);
		dfs(map, y - 1, x, d);
		dfs(map, y, x + 1, d);
		dfs(map, y, x - 1, d);
	}
}

char	**map_cpy(char **map, int y, int x)
{
	int		i;
	int		j;
	char	**new_map;

	new_map = malloc(sizeof(char *) * (y + 1));
	if (!new_map)
		return (write(1, RED, 5), write(2, \
			"Malloc failed mmmm!\n", 20), write(1, RESET, 4), NULL);
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

int	valid_map(t_data *d, char **map)
{
	char	**cp_map;

	int (y), (x), (c), (e);
	(assign_player_pos(d), cp_map = map_cpy(map, d->map_height, d->map_width));
	if (!cp_map)
		return (0);
	(dfs(cp_map, d->y, d->x, d), c = 0, y = 0, e = 0);
	while (++y >= 1 && y < d->map_height)
	{
		x = 0;
		while (++x >= 1 && x < d->map_width)
		{
			if (cp_map[y][x] == 'C')
				c++;
			else if (cp_map[y][x] == 'E')
				e++;
		}
	}
	if (c > 0 || e > 0)
		(write(1, RED, 5), write(2, "Error: Invalid Map\n", 19), write(1, \
		"Because the following goals isn't true\n", 39), write(1, \
		"The player's goal is to collect every collectible present on the map"\
		, 68), write(1, ", then escape chosing the shortest possible route!\n"\
		, 51), write(1, RESET, 4));
	return (free_map(cp_map, d->map_height), (c == 0 && e == 0));
}

void	calculate_y_x(t_data *d, char **av)
{
	char	*s;

	int (i), (fd);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		(write(2, "The file doesn't exist\n", 23), exit(1));
	s = get_next_line(fd, 0);
	d->map_width = ft_strlen(s) - 1;
	if (ft_strlen(s) == 0)
		(write(1, "Error\n", 6), free(s), exit(1));
	while (s)
	{
		i = -1;
		while (++i >= 0 && s[i])
			if (s[i] == '\n')
				d->map_height++;
		if ((ft_strlen(s)) == 1 || ft_strlen(s) > (d->map_width + 1) || \
		(ft_strlen(s) > d->map_width && !ft_strchr_1(s, '\n')) || \
		ft_strlen(s) < d->map_width)
			(write(1, "Error\n", 6), free(s), get_next_line(fd, 1), exit(1));
		if (!ft_strchr_1(s, '\n'))
			d->map_height++;
		(free(s), s = get_next_line(fd, 0));
	}
	close(fd);
}
