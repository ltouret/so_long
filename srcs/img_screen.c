/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 03:03:15 by ltouret           #+#    #+#             */
/*   Updated: 2021/09/20 03:03:25 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	img_screen(t_text_img *img, t_img *mimg, int x, int y)
{
	char	*dst;
	int		text[2];
	int		new_coord[2];
	int		oy;

	ft_bzero(&text, sizeof(text));
	oy = y;
	new_coord[0] = x + 32;
	new_coord[1] = y + 32;
	while (x < new_coord[0])
	{
		y = oy;
		text[1] = 0;
		while (y < new_coord[1])
		{
			dst = img->addr + (text[1] * img->line_length + text[0]
					* (img->bpp / 8));
			if (*(unsigned int *)dst != 0xff000000)
				my_mlx_pixel_put(mimg, x, y, *((unsigned int *)dst));
			text[1]++;
			y++;
		}
		text[0]++;
		x++;
	}
}
