/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:59:27 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/27 20:44:42 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

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

	ft_check_args(argc, &data);
	ft_init_map(&data, argv[1]);
	ft_validate_map(&data);
	if (ft_fill(&data))
		ft_free_exit(&data, EXIT_FAILURE);
	ft_init_graphics(&data);
	render_map(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, on_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
