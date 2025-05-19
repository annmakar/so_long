/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n <n@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:59:27 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/20 00:55:16 by n                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_destroy(t_data *data)
{
	ft_printf("You closed the window. Bye!\n");
	exit_game(data);
	return (0);
}

void	destroy_all(t_data *data)
{
	destroy_images(data);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map(data->map);
	exit(EXIT_SUCCESS);
}

void	exit_game(t_data *data)
{
	destroy_all(data);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./so_long map_file.ber\n", 2);
		return (1);
	}

	data.map = load_map(argv[1]);
	if (!data.map)
	{
		ft_putstr_fd("Error\nFailed to load map\n", 2);
		return (1);
	}

	// Calculate dimensions
	data.map_height = 0;
	while (data.map[data.map_height])
		data.map_height++;
	data.map_width = ft_strlen(data.map[0]);

	// Map Validations
	validate_map_rectangular(data.map, data.map_height);         //  Rectangular
	validate_map_elements(data.map);                             //  Valid characters and counts
	validate_map_walls(data.map, data.map_width, data.map_height); //  Walls around

	// Initialize game data
	data.move_count = 0;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		free_map(data.map);
		return (1);
	}

	load_images(&data);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
		data.map_width * TILE_SIZE,
		data.map_height * TILE_SIZE,
		"so_long");
	if (!data.win_ptr)
	{
		destroy_images(&data);
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		free_map(data.map);
		return (1);
	}

	render_map(&data);
	// Event hooks
	mlx_hook(data.win_ptr, 2, 1L << 0, on_keypress, &data);  // KeyPress event
	/*data.win_ptr — The window to listen for events on.
2 — The event code for KeyPress event (when a key is pressed). from x11
1L << 0 — it tells the system to listen for this event.
on_keypress — called when a key is pressed.
&data — A pointer to t_data struct, passed to the callback to access program state inside the handler.*/
	mlx_hook(data.win_ptr, 17, 0, on_destroy, &data);        // Close window event
	/*17 — The event code for the window close event
0 — No event mask needed
on_destroy — function that handles cleanup and exit when the user closes the window.
&data — data pointer passed to on_destroy.*/
	mlx_loop(data.mlx_ptr);
	return (0);
}

