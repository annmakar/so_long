/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:12:57 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/27 21:14:02 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	floodfill(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
		return ;
	if (data->map[y][x] == '1' || data->map[y][x] == 'o' ||
		data->map[y][x] == 'c' || data->map[y][x] == 'e')
		return ;
	if (data->map[y][x] == '0')
		data->map[y][x] = 'o';
	else if (data->map[y][x] == 'C')
		data->map[y][x] = 'c';
	else if (data->map[y][x] == 'E')
	{
		data->map[y][x] = 'e';
		return ;
	}
	floodfill(data, x + 1, y);
	floodfill(data, x - 1, y);
	floodfill(data, x, y + 1);
	floodfill(data, x, y - 1);
}

static void	floodrefill(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
		return ;
	if (data->map[y][x] == '1' || data->map[y][x] == '0'
		|| data->map[y][x] == 'C' || data->map[y][x] == 'E')
		return ;
	if (data->map[y][x] == 'o')
		data->map[y][x] = '0';
	else if (data->map[y][x] == 'c')
		data->map[y][x] = 'C';
	else if (data->map[y][x] == 'e')
	{
		data->map[y][x] = 'E';
		return ;
	}
	floodrefill(data, x + 1, y);
	floodrefill(data, x - 1, y);
	floodrefill(data, x, y + 1);
	floodrefill(data, x, y - 1);
}

int	ft_fill(t_data *data)
{
	int	y;
	int	x;

	floodfill(data, data->player_x, data->player_y);
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'E' || data->map[y][x] == 'C')
			{
				ft_putstr_fd("Error\nExit or collectible unreachable\n", 2);
				return (1);
			}
			++x;
		}
		++y;
	}
	floodrefill(data, data->player_x, data->player_y);
	return (0);
}

void	ft_free_exit(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->map)
			free_map(data->map);
		ft_bzero(data, sizeof(t_data));
	}
	exit(exit_code);
}

void	ft_validate_map(t_data *data)
{
	validate_map_rectangular(data->map, data->map_height, data);
	validate_map_elements(data->map, data);
	validate_map_walls(data->map, data->map_width, data->map_height, data);
}
