/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:26:35 by ltouret           #+#    #+#             */
/*   Updated: 2021/09/20 03:05:52 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_floor(t_data *data, t_img *mimg)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mimg->img = mlx_new_image(data->mlx.mlx,
			data->mlx.mlx_wid, data->mlx.mlx_hei);
	mimg->addr = mlx_get_data_addr(mimg->img, &mimg->bpp, &mimg->line_length,
			&mimg->endian);
	while (x < data->mlx.mlx_wid)
	{
		y = 0;
		while (y < data->mlx.mlx_hei)
		{
			my_mlx_pixel_put(mimg, x, y, 0x009cd3db);
			y++;
		}
		x++;
	}
}

static void	draw_map(t_data *data, t_img *mimg)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				img_screen(&data->mlx.wa_text, mimg, x * 32, y * 32);
			else if (data->map[y][x] == 'C')
				img_screen(&data->mlx.co_text, mimg, x * 32, y * 32);
			else if (data->map[y][x] == 'E')
				img_screen(&data->mlx.ex_text, mimg, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

static void	draw_player(t_data *data, t_img *mimg)
{
	t_text_img	*player;

	if (data->player.dir == 'u')
		player = &data->mlx.up_text;
	else if (data->player.dir == 'd')
		player = &data->mlx.do_text;
	else if (data->player.dir == 'l')
		player = &data->mlx.le_text;
	else if (data->player.dir == 'r')
		player = &data->mlx.ri_text;
	img_screen(player, mimg, data->player.x * 32, data->player.y * 32);
}

void	draw_img(t_data *data)
{
	t_img	mimg;

	draw_floor(data, &mimg);
	draw_map(data, &mimg);
	draw_player(data, &mimg);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, mimg.img, 0, 0);
	mlx_destroy_image(data->mlx.mlx, mimg.img);
}
