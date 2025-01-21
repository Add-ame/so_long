/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddame <maddame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:55:28 by maddame           #+#    #+#             */
/*   Updated: 2025/01/21 09:55:59 by maddame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "/usr/include/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define UP_KEY 65362
# define DOWN_KEY 65364
# define D 100
# define A 97
# define S 115
# define W 119

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		y;
	int		x;
	int		i;
	int		j;
	char	c;
	char	o;
	char	n;
	int		num_mov;
	int		coins;
	int		frame;
	int		frame_p_e;
	t_img	player[9];
	t_img	player_exit;
	t_img	background;
	t_img	coin;
	t_img	wall;
	t_img	exitt;
	t_img	exit_2;
	t_img	enemy;
	int		wall_count;
	int		collectibles_count;
	int		player_count;
	int		exit_count;
	int		enemy_count;
	int		free_space_count;
	int		frame_slower;
}	t_data;

char	*get_next_line(int fd, int flag);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(char *s);
int		close_win(t_data *d);
int		ft_strchr_1(const char *s, int c);

/*  main*/
void	init_null(t_data *d);
void	initialize(t_data *d);
void	cleaning_player(t_data *d);
void	cleaning(t_data *d);

/* handle key*/
void	move_player_1(t_data *d, int new_y, int new_x);
void	move_player(t_data *d, int new_y, int new_x);
void	assign_player_pos(t_data *d);
int		handle_key_press(int keycode, t_data *d);
void	update_animation(t_data *d);

/* tools*/
void	load_player(t_data *d);
void	load_imgs(t_data *d);
void	put_img_to_map(t_data *d, char **map);
void	keep_puting(t_data *d);
void	puting(t_data *d);

/*check_map*/
char	**fill_map(t_data *d, char **av, char **map);
char	**take_map(t_data *d, char **av);
int		display_error(t_data *d);
int		to_long(t_data *d);
int		check_map(t_data *d);

/*valid it*/
void	dfs(char **map, int y, int x, t_data *d);
char	**map_cpy(char **map, int y, int x);
void	free_map(char **pt, int y);
int		valid_map(t_data *d, char **map);
void	calculate_y_x(t_data *d, char **av);

#endif
