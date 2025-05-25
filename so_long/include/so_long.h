/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:28:23 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/25 21:52:39 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <X11/keysym.h>

# include "ft_printf.h"
# include "libft.h"
# include "../mlx/mlx.h"
# include "get_next_line.h"

# define TILE_SIZE 32
# define MAX_LINES 1000

#ifndef KEYS_H
#define KEYS_H

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define AR_UP	    65362
# define AR_DOWN	65364
# define AR_LEFT	65361
# define AR_RIGHT	65363

// # define KEY_W     XK_w
// # define KEY_A     XK_a
// # define KEY_S     XK_s
// # define KEY_D     XK_d
// # define KEY_ESC   XK_Escape
// # define KEY_UP    XK_Up
// # define KEY_DOWN  XK_Down
// # define KEY_LEFT  XK_Left
// # define KEY_RIGHT XK_Right
#endif

typedef struct s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_collectible;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		move_count;
	int		collectible_count;
} t_data;

// main logic
void	render_map(t_data *data);
void	move_player(t_data *data, int new_x, int new_y);
int		on_keypress(int keysym, t_data *data);
int		on_destroy(t_data *data);

// image & memory
void	load_images(t_data *data);
void	destroy_images(t_data *data);
void	free_map(char **map);
void	destroy_all(t_data *data);
void	exit_game(t_data *data);

// map
char	**load_map(const char *filename);
void	validate_map_rectangular(char **map, int height);
// so_long.h
void	validate_map_rectangular(char **map, int height);
void	validate_map_elements(char **map, t_data *data);
void	validate_map_walls(char **map, int width, int height);

#endif
