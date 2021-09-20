/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:17:12 by ltouret           #+#    #+#             */
/*   Updated: 2021/09/20 02:54:16 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	collect(t_data *data)
{
	if (data->map[data->player.y][data->player.x] == 'C')
	{
		data->map[data->player.y][data->player.x] = '0';
		data->player.col--;
	}
}

static void	end_game(t_data *data)
{
	if (data->map[data->player.y][data->player.x] == 'E')
	{
		if (data->player.col > 0)
			return ;
		else
			clean_exit(data);
	}
}

static void	move_ws(t_data *data, int move)
{
	if (move == -1)
		data->player.dir = 'u';
	else
		data->player.dir = 'd';
	if ((data->map[data->player.y + move][data->player.x] != 'E'
		|| data->player.col == 0)
		&& data->map[data->player.y + move][data->player.x] != '1')
	{
		data->player.y += move;
		data->player.mov++;
		printf("%d\n", data->player.mov);
	}
}

static void	move_ad(t_data *data, int move)
{
	if (move == -1)
		data->player.dir = 'l';
	else
		data->player.dir = 'r';
	if ((data->map[data->player.y][data->player.x + move] != 'E'
		|| data->player.col == 0)
			&& data->map[data->player.y][data->player.x + move] != '1')
	{
		data->player.x += move;
		data->player.mov++;
		printf("%d\n", data->player.mov);
	}
}

int	keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
		clean_exit(data);
	else if (key == KEY_W)
		move_ws(data, -1);
	else if (key == KEY_S)
		move_ws(data, 1);
	else if (key == KEY_D)
		move_ad(data, 1);
	else if (key == KEY_A)
		move_ad(data, -1);
	collect(data);
	end_game(data);
	draw_img(data);
	return (OK);
}
