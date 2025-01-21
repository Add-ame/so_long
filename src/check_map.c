/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddame <maddame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:09:55 by maddame           #+#    #+#             */
/*   Updated: 2025/01/21 10:03:03 by maddame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**fill_map(t_data *d, char **av, char **map)
{
	char	*s;
	int		fd;

	fd = open(av[1], O_RDONLY);
	d->i = -1;
	s = get_next_line(fd, 0);
	while (++d->i >= 0 && d->i < d->map_height)
	{
		map[d->i] = malloc(sizeof(char) * (d->map_width + 1));
		if (!map[d->i])
			return (NULL);
		d->j = -1;
		while (++d->j >= 0 && d->j < d->map_width)
		{
			if (s[d->j] == 'C')
				d->coins++;
			map[d->i][d->j] = s[d->j];
		}
		map[d->i][d->j] = '\0';
		free(s);
		s = get_next_line(fd, 0);
	}
	map[d->i] = NULL;
	close(fd);
	return (map);
}

char	**take_map(t_data *d, char **av)
{
	char		**map;
	char		*arr;
	int			i;
	int			len;

	arr = ".ber";
	len = ft_strlen(av[1]);
	i = len - 4;
	while (av[1][i])
	{
		if (av[1][i] != arr[i - (len - 4)])
			return (write(1, RED, 5), write(2, \
			"Ensure map file extension is: .ber\n", 35), \
			write(1, RESET, 4), NULL);
		i++;
	}
	calculate_y_x(d, av);
	map = malloc(sizeof(char *) * (d->map_height + 1));
	if (!map)
		return (write(1, RED, 5), write(2, \
			"Malloc failed mmmm microb!\n", 27), write(1, RESET, 4), NULL);
	return (fill_map(d, av, map));
}

int	display_error(t_data *d)
{
	if (d->map_height == d->map_width)
		return (write(1, RED, 5), write(2, \
			"The map must be rectangular\n", 28), write(1, RESET, 4), 0);
	if (d->enemy_count < 1)
		return (write(1, RED, 5), write(2, "Error: Invalid Map\n", 19), write(1, \
		"There should be at least one ENEMY in the map\n", 46), \
		write(1, RESET, 4), 0);
	if (d->collectibles_count < 1)
		return (write(1, RED, 5), write(2, "Error: Invalid Map\n", 19), write(1, \
		"There should be at least one COLLECTIBLES in the map\n", 53), \
		write(1, RESET, 4), 0);
	if (d->player_count != 1)
		return (write(1, RED, 5), write(2, "Error: Invalid Map\n", 19), write(1, \
		"There should be one PLAYER in the map\n", 38), \
		write(1, RESET, 4), 0);
	if (d->exit_count != 1)
		return (write(1, RED, 5), write(2, "Error: Invalid Map\n", 19), write(1, \
		"There should be one EXIT in the map\n", 36), \
		write(1, RESET, 4), 0);
	return (1);
}

int	to_long(t_data *d)
{
	if (d->map[d->y][0] != '1' || d->map[d->y][d->map_width - 1] != '1' \
		|| d->map[0][0] != '1' || d->map[0][d->x] != '1' || \
		d->map[d->map_height - 1][0] != '1' || \
		d->map[d->map_height - 1][d->x] != '1')
		return (write(1, RED, 5), write(2, "Error: Invalid Map\n", 19), write(1, \
		"The map must be closed/surrounded by walls\n", 43), \
		write(1, RESET, 4), 0);
	if (d->map[d->y][d->x] == '1')
		d->wall_count++;
	else if (d->map[d->y][d->x] == 'P')
		d->player_count++;
	else if (d->map[d->y][d->x] == 'C')
		d->collectibles_count++;
	else if (d->map[d->y][d->x] == 'E')
		d->exit_count++;
	else if (d->map[d->y][d->x] == '0')
		d->free_space_count++;
	else if (d->map[d->y][d->x] == 'D')
		d->enemy_count++;
	else
		return (write(1, RED, 5), write(2, \
	"Error: Invalid Map\nThe map should has only the following: P E 1 0 C D\n"\
	, 70), write(1, RESET, 4), 0);
	return (1);
}

int	check_map(t_data *d)
{
	d->y = -1;
	while (++d->y >= 0 && d->y < d->map_height)
	{
		d->x = -1;
		while (++d->x >= 0 && d->x < d->map_width)
		{
			if (!to_long(d))
				return (0);
		}
	}
	return (display_error(d) != 0);
}
