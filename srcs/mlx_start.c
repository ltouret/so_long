/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:50:33 by ltouret           #+#    #+#             */
/*   Updated: 2021/09/20 03:08:06 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	load_textures1(t_data *data)
{
	data->mlx.ex_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./textures/exit.xpm", &data->mlx.ri_text.wid,
			&data->mlx.ri_text.hei);
	data->mlx.wa_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./textures/wall.xpm", &data->mlx.ri_text.wid,
			&data->mlx.ri_text.hei);
	if (data->mlx.up_text.img == NULL
		|| data->mlx.do_text.img == NULL
		|| data->mlx.le_text.img == NULL || data->mlx.ri_text.img == NULL
		|| data->mlx.co_text.img == NULL || data->mlx.ex_text.img == NULL
		|| data->mlx.wa_text.img == NULL)
		panic(ERR_TEXT);
}

static void	load_textures(t_data *data)
{
	data->mlx.up_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./textures/up.xpm", &data->mlx.up_text.wid,
			&data->mlx.up_text.hei);
	data->mlx.do_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./textures/down.xpm", &data->mlx.do_text.wid,
			&data->mlx.do_text.hei);
	data->mlx.le_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./textures/left.xpm", &data->mlx.le_text.wid,
			&data->mlx.le_text.hei);
	data->mlx.ri_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./textures/right.xpm", &data->mlx.ri_text.wid,
			&data->mlx.ri_text.hei);
	data->mlx.co_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./textures/coll.xpm", &data->mlx.ri_text.wid,
			&data->mlx.ri_text.hei);
	load_textures1(data);
}

static void	load_textures_addr1(t_data *data)
{
	data->mlx.up_text.addr = mlx_get_data_addr(data->mlx.up_text.img,
			&data->mlx.up_text.bpp, &data->mlx.up_text.line_length,
			&data->mlx.up_text.endian);
	data->mlx.do_text.addr = mlx_get_data_addr(data->mlx.do_text.img,
			&data->mlx.do_text.bpp, &data->mlx.do_text.line_length,
			&data->mlx.do_text.endian);
	data->mlx.le_text.addr = mlx_get_data_addr(data->mlx.le_text.img,
			&data->mlx.le_text.bpp, &data->mlx.le_text.line_length,
			&data->mlx.le_text.endian);
	data->mlx.ri_text.addr = mlx_get_data_addr(data->mlx.ri_text.img,
			&data->mlx.ri_text.bpp, &data->mlx.ri_text.line_length,
			&data->mlx.ri_text.endian);
	data->mlx.ex_text.addr = mlx_get_data_addr(data->mlx.ex_text.img,
			&data->mlx.ex_text.bpp, &data->mlx.ex_text.line_length,
			&data->mlx.ex_text.endian);
	data->mlx.wa_text.addr = mlx_get_data_addr(data->mlx.wa_text.img,
			&data->mlx.wa_text.bpp, &data->mlx.wa_text.line_length,
			&data->mlx.wa_text.endian);
	data->mlx.co_text.addr = mlx_get_data_addr(data->mlx.co_text.img,
			&data->mlx.co_text.bpp, &data->mlx.co_text.line_length,
			&data->mlx.co_text.endian);
}

void	mlx_start(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		panic(ERR_MLX);
	data->mlx.mlx_wid = data->map_width * 32;
	data->mlx.mlx_hei = data->map_height * 32;
	load_textures(data);
	load_textures_addr1(data);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			data->mlx.mlx_wid, data->mlx.mlx_hei, "so_long");
}
