/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:58:37 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/27 22:11:21 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**load_map(const char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;
	int		len;

	i = 0;
	map = malloc(sizeof(char *) * (MAX_LINES + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	put_tile(t_data *data, int x, int y, void *img)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		img, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				put_tile(data, x, y, data->img_wall);
			else if (data->map[y][x] == '0')
				put_tile(data, x, y, data->img_floor);
			else if (data->map[y][x] == 'P')
				put_tile(data, x, y, data->img_player);
			else if (data->map[y][x] == 'E')
				put_tile(data, x, y, data->img_exit);
			else if (data->map[y][x] == 'C')
				put_tile(data, x, y, data->img_collectible);
			x++;
		}
		y++;
	}
}

void	load_images(t_data *data)
{
	int	width;
	int	height;

	width = TILE_SIZE;
	height = TILE_SIZE;
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/walls.xpm", &width, &height);
	data->img_floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/floor.xpm", &width, &height);
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/player.xpm", &width, &height);
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/exit.xpm", &width, &height);
	data->img_collectible = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/collectible.xpm", &width, &height);
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
