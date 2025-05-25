/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:58:20 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/25 22:05:59 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	validate_map_elements(char **map, t_data *data)
{
	int	y = 0;
	int	x;
	int	player_count = 0;
	int	exit_count = 0;

	data->collectible_count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				player_count++;
			}
			else if (map[y][x] == 'E')
				exit_count++;
			else if (map[y][x] == 'C')
				data->collectible_count++;
			else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != '\n')
			{
				ft_putstr_fd("Error\nInvalid character in map\n", 2);
				exit(EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}

	if (player_count != 1 || exit_count != 1 || data->collectible_count == 0)
	{
		ft_putstr_fd("Error\nMap must have 1 player, at least 1 exit and 1 collectible\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	validate_map_walls(char **map, int width, int height)
{
	int	x;
	int	y;

	// Top and bottom row
	for (x = 0; x < width - 1; x++)
	{
		ft_printf("%i, %c, %c\n", x,map[0][x],map[height - 1][x]);
		if (map[0][x] != '1' || map[height - 1][x] != '1')
		{
			ft_printf("%i, %c, %c\n", x,map[0][x],map[height - 1][x]);
			ft_putstr_fd("Error1\nMap not surrounded by walls\n", 2);
			exit(EXIT_FAILURE);
		}
	}

	// First and last column
	for (y = 0; y < height - 1; y++)
	{
		if (map[y][0] != '1' || map[y][width - 1] != '1')
		{
			ft_printf("%i, %c, %c\n", y,map[y][0],map[y][width - 1]);
			ft_putstr_fd("Error2\nMap not surrounded by walls\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	validate_map_rectangular(char **map, int height) //check if every row has the same length
{
	int	i;
	int	len;

	i = 1;
	if (height == 0)
	{
		ft_putstr_fd("Error\nMap is empty\n", 2);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(map[0]); //len of the 1 row
	while (i < height)
	{
		if ((int)ft_strlen(map[i]) != len) //if some of rows not the same length as 1, faaaaail
		{
			ft_putstr_fd("Error\nMap is not rectangular\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}