/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:31:54 by ltouret           #+#    #+#             */
/*   Updated: 2021/09/20 02:51:25 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = get_data();
	parsing(argc, argv, data);
	validate_map(data);
	mlx_start(data);
	draw_img(data);
	mlx_mouse_hide(data->mlx.mlx, data->mlx.mlx_win);
	mlx_hook(data->mlx.mlx_win, 2, 1L << 0, keypress, data);
	mlx_hook(data->mlx.mlx_win, 17, 1L << 17, clean_exit, data);
	mlx_loop(data->mlx.mlx);
	return (0);
}
