#include "so_long.h"

void	validate_map_elements(char **map)
{
	int	y = 0;
	int	x;
	int	player_count = 0;
	int	exit_count = 0;
	int	collectible_count = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				player_count++;
			else if (map[y][x] == 'E')
				exit_count++;
			else if (map[y][x] == 'C')
				collectible_count++;
			else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != '\n')
			{
				ft_putstr_fd("Error\nInvalid character in map\n", 2);
				exit(EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}

	if (player_count != 1 || exit_count == 0 || collectible_count == 0)
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
	for (x = 0; x < width; x++)
	{
		if (map[0][x] != '1' || map[height - 1][x] != '1')
		{
			ft_putstr_fd("Error\nMap not surrounded by walls\n", 2);
			exit(EXIT_FAILURE);
		}
	}

	// First and last column
	for (y = 0; y < height; y++)
	{
		if (map[y][0] != '1' || map[y][width - 1] != '1')
		{
			ft_putstr_fd("Error\nMap not surrounded by walls\n", 2);
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