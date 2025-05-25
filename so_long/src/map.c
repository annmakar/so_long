/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:58:37 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/25 22:03:26 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

char	**load_map(const char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (MAX_LINES + 1)); // MAX_LINES = your max map height
	if(!map)
		return(NULL);
	fd = open(filename, O_RDONLY); //o_rdonly open file for reading only
	if (fd < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		int len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i++] = line;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	render_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)  //Keep looping as long as y is less than the map height
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_floor, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_player, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_exit, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}
/*data->mlx_ptr = MLX instance
data->win_ptr = window
data->img_wall = image of a wall
x * TILE_SIZE = horizontal pixel position
y * TILE_SIZE = vertical pixel position */

void	load_images(t_data *data)
{
	int	width;
	int	height;

	width = TILE_SIZE;
	height = TILE_SIZE;
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/walls.xpm", &width, &height);
	data->img_floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/floor.xpm", &width, &height);
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/player.xpm", &width, &height);
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/exit.xpm", &width, &height);
	data->img_collectible = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/collectible.xpm", &width, &height);
	if (!data->img_wall || !data->img_floor || !data->img_player
		|| !data->img_exit || !data->img_collectible)
	{
		ft_putstr_fd("Error: Failed to load one or more textures\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	destroy_images(t_data *data)
{
	if (data->img_wall)
		mlx_destroy_image(data->mlx_ptr, data->img_wall);
	if (data->img_floor)
		mlx_destroy_image(data->mlx_ptr, data->img_floor);
	if (data->img_player)
		mlx_destroy_image(data->mlx_ptr, data->img_player);
	if (data->img_exit)
		mlx_destroy_image(data->mlx_ptr, data->img_exit);
	if (data->img_collectible)
		mlx_destroy_image(data->mlx_ptr, data->img_collectible);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}