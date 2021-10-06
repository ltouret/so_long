/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:45:43 by ltouret           #+#    #+#             */
/*   Updated: 2021/10/06 17:59:22 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_map1(t_data *data, t_check *check, int i)
{
	int	o;

	o = 0;
	while (data->map[i][o])
	{
		if (data->map[i][o] == '0' || data->map[i][o] == '1'
			|| data->map[i][o] == 'C' || data->map[i][o] == 'E'
			|| data->map[i][o] == 'P')
		{
			if (data->map[i][o] == 'P')
			{
				if (check->player == 1)
					panic(ERR_MAP_MANY_PLAY);
				check->player = 1;
			}
			if (data->map[i][o] == 'E')
				check->exit = 1;
			if (data->map[i][o] == 'C')
				check->collec = 1;
		}
		else
			panic(ERR_MAP_WCHAR);
		o++;
	}
}

static void	check_map(t_data *data)
{
	int		i;
	t_check	check;

	i = 0;
	ft_bzero(&check, sizeof(t_check));
	data->map_width = ft_strlen(data->map[0]);
	while (data->map[i])
	{
		if (data->map[i][0] == '\0')
			panic(ERR_MAP_WCHAR);
		check_map1(data, &check, i);
		if (data->map_width != ft_strlen(data->map[i]))
			panic(ERR_MAP_RECT);
		i++;
	}
	if (check.player == 0)
		panic(ERR_MAP_NO_PLAY);
	if (check.collec == 0)
		panic(ERR_MAP_COLL);
	if (check.exit == 0)
		panic(ERR_MAP_EXIT);
}

static void	get_data_map(t_data *data)
{
	int	i;
	int	o;

	i = 0;
	while (data->map[i])
	{
		o = 0;
		while (data->map[i][o])
		{
			if (data->map[i][o] == 'C')
				data->player.col++;
			if (data->map[i][o] == 'P')
			{
				data->player.x = o;
				data->player.y = i;
				data->player.dir = 'u';
				data->map[i][o] = '0';
			}
			o++;
		}
		i++;
	}
}

static void	check_map_closed(t_data *data)
{
	int	i;
	int	o;

	i = 0;
	while (data->map[i])
	{
		o = 0;
		while (data->map[i][o])
		{
			if ((i == 0 || i == data->map_height - 1)
				|| (o == 0 || o == data->map_width - 1))
			{
				if (data->map[i][o] != '1')
					panic(ERR_MAP_OPEN);
			}
			o++;
		}
		i++;
	}
}

void	validate_map(t_data *data)
{
	check_map(data);
	get_data_map(data);
	check_map_closed(data);
}
