/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:53:25 by ltouret           #+#    #+#             */
/*   Updated: 2021/10/05 00:59:11 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	clean_exit(t_data *data)
{
	int	i;

	mlx_destroy_image(data->mlx.mlx, data->mlx.up_text.img);
	mlx_destroy_image(data->mlx.mlx, data->mlx.do_text.img);
	mlx_destroy_image(data->mlx.mlx, data->mlx.le_text.img);
	mlx_destroy_image(data->mlx.mlx, data->mlx.ri_text.img);
	mlx_destroy_image(data->mlx.mlx, data->mlx.wa_text.img);
	mlx_destroy_image(data->mlx.mlx, data->mlx.ex_text.img);
	mlx_destroy_image(data->mlx.mlx, data->mlx.co_text.img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	exit(0);
	return (OK);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

t_data	*get_data(void)
{
	static t_data	data;

	if (data.init == 0)
	{
		ft_bzero(&data, sizeof(t_data));
		data.init = 1;
	}
	return (&data);
}

void	*mymalloc(size_t size)
{
	void	*out;

	out = malloc(size);
	if (out == NULL)
		panic(ERR_MALLOC);
	ft_bzero(out, size);
	return (out);
}

char	*ft_strdup(char *str)
{
	char	*outstr;
	int		i;

	if (str == NULL)
		return (NULL);
	outstr = mymalloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	while (str[i])
	{
		outstr[i] = str[i];
		i++;
	}
	outstr[i] = '\0';
	return (outstr);
}
