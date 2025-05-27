/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:58:20 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/27 20:04:05 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_map_char(t_data *data, char c, t_point pos, \
	t_map_counters *counters)
{
	if (c == 'P')
	{
		data->player_x = pos.x;
		data->player_y = pos.y;
		counters->player_count++;
	}
	else if (c == 'E')
		counters->exit_count++;
	else if (c == 'C')
		data->collectible_count++;
	else if (c != '0' && c != '1' && c != '\n')
	{
		ft_putstr_fd("Error\nInvalid character in map\n", 2);
		ft_free_exit(data, EXIT_FAILURE);
	}
}

static void	validate_counts(t_data *data, t_map_counters *counters)
{
	if (counters->player_count != 1 || counters->exit_count != 1 \
		|| data->collectible_count == 0)
	{
		ft_putstr_fd("Error\nMap must have 1 player, at least 1 exit\
			 and 1 collectible\n", 2);
		ft_free_exit(data, EXIT_FAILURE);
	}
}

void	validate_map_elements(char **map, t_data *data)
{
	t_point			pos;
	t_map_counters	counters;
	int				y;
	int				x;

	y = 0;
	counters.player_count = 0;
	counters.exit_count = 0;
	data->collectible_count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			pos.x = x;
			pos.y = y;
			handle_map_char(data, map[y][x], pos, &counters);
			x++;
		}
		y++;
	}
	validate_counts(data, &counters);
}

void	validate_map_walls(char **map, int width, int height, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < width - 1)
	{
		if (map[0][x] != '1' || map[height - 1][x] != '1')
		{
			ft_putstr_fd("Error\nMap not surrounded by walls\n", 2);
			ft_free_exit(data, EXIT_FAILURE);
		}
		x++;
	}
	y = 0;
	while (y < height - 1)
	{
		if (map[y][0] != '1' || map[y][width - 1] != '1')
		{
			ft_putstr_fd("Error\nMap not surrounded by walls\n", 2);
			ft_free_exit(data, EXIT_FAILURE);
		}
		y++;
	}
}

void	validate_map_rectangular(char **map, int height, t_data *data)
{
	int	i;
	int	len;

	i = 1;
	if (height == 0)
	{
		ft_putstr_fd("Error\nMap is empty\n", 2);
		ft_free_exit(data, EXIT_FAILURE);
	}
	len = ft_strlen(map[0]);
	while (i < height)
	{
		if ((int)ft_strlen(map[i]) != len)
		{
			ft_putstr_fd("Error\nMap is not rectangular\n", 2);
			ft_free_exit(data, EXIT_FAILURE);
		}
		i++;
	}
}
