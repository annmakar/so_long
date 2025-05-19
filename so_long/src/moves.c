#include "so_long.h"

void	move_player(t_data *data, int new_x, int new_y)
{
	char next_tile = data->map[new_y][new_x];

	if (next_tile == '1') // Wall
		return;

	if (next_tile == 'C') // Collectible
	{
		data->collectible_count--;
		data->map[new_y][new_x] = '0'; // remove collectible
	}
	if (next_tile == 'E' && data->collectible_count == 0)
	{
		ft_printf("You won!\n");
		exit_game(data);
		return;
	}
	if (new_x < 0 || new_x >= data->map_width || new_y < 0 || new_y >= data->map_height)
  	  return;
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

    if (keysym == KEY_W || keysym == KEY_UP)
        new_y--;
    else if (keysym == KEY_S || keysym == KEY_DOWN)
        new_y++;
    else if (keysym == KEY_A || keysym == KEY_LEFT)
        new_x--;
    else if (keysym == KEY_D || keysym == KEY_RIGHT)
        new_x++;
    else if (keysym == KEY_ESC)
        exit_game(data);

    move_player(data, new_x, new_y);
    return (0);
}

