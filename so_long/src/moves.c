/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annmakar <annmakar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:58:31 by annmakar          #+#    #+#             */
/*   Updated: 2025/05/25 22:11:42 by annmakar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	move_player(t_data *data, int new_x, int new_y)
{
	char next_tile = data->map[new_y][new_x];

	if (next_tile == '1' || (next_tile == 'E' && data->collectible_count != 0))
		return;
	if (next_tile == 'C') // Collectible
	{
		data->collectible_count--;
	}
	if (next_tile == 'E' && data->collectible_count == 0)
	{
		ft_printf("You won!\n");
		exit_game(data);
		return;
	}
	data->map[data->player_y][data->player_x] = '0'; // clear old pos
	data->player_x = new_x;
	data->player_y = new_y;
	data->map[new_y][new_x] = 'P'; // move player to new pos
	data->move_count++;
	ft_printf("Moves: %d\n", data->move_count);
	render_map(data); // redraw full map for now
}

int on_keypress(int keysym, t_data *data)
{
    int new_x = data->player_x;
    int new_y = data->player_y;

    if (keysym == 119 || keysym == 65362)
        new_y--;
    else if (keysym == 115 || keysym == 65364)
        new_y++;
    else if (keysym == 97 || keysym == 65361)
        new_x--;
    else if (keysym == 100 || keysym == 65363)
        new_x++;
    else if (keysym == 65307)
        exit_game(data);

    move_player(data, new_x, new_y);
    return (0);
}

