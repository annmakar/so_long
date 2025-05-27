/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:58:31 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/27 20:43:25 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_data *data, int new_x, int new_y)
{
	char	next_tile;

	next_tile = data->map[new_y][new_x];
	if (next_tile == '1'
		|| (next_tile == 'E' && data->collectible_count != 0))
		return ;
	if (next_tile == 'C')
		data->collectible_count--;
	if (next_tile == 'E' && data->collectible_count == 0)
	{
		ft_printf("You won!\n");
		exit_game(data);
		return ;
	}
	data->map[data->player_y][data->player_x] = '0';
	data->player_x = new_x;
	data->player_y = new_y;
	data->map[new_y][new_x] = 'P';
	data->move_count++;
	ft_printf("Moves: %d\n", data->move_count);
	render_map(data);
}

int	on_keypress(int keysym, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (keysym == 119 || keysym == 65362)
		new_y--;
	else if (keysym == 115 || keysym == 65364)
		new_y++;
	else if (keysym == 97 || keysym == 65361)
		new_x--;
	else if (keysym == 100 || keysym == 65363)
		new_x++;
	else if (keysym == 65307)
	{
		exit_game(data);
		return (0);
	}
	move_player(data, new_x, new_y);
	return (0);
}

void	ft_init_graphics(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		exit_game(data);
	}
	load_images(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->map_width * TILE_SIZE,
			data->map_height * TILE_SIZE,
			"so_long");
	if (!data->win_ptr)
	{
		destroy_images(data);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit_game(data);
	}
}

void	ft_check_args(int argc, t_data *data)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./so_long map_file.ber\n", 2);
		exit_game(data);
	}
}

void	ft_init_map(t_data *data, char *filename)
{
	data->map = load_map(filename);
	if (!data->map)
	{
		ft_putstr_fd("Error\nFailed to load map\n", 2);
		exit(EXIT_FAILURE);
	}
	data->map_height = 0;
	while (data->map[data->map_height])
		data->map_height++;
	data->map_width = ft_strlen(data->map[0]);
	data->move_count = 0;
}
