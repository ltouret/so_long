/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:53:38 by ltouret           #+#    #+#             */
/*   Updated: 2021/10/06 19:26:44 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

static void	add_map(char *buf, t_data *data)
{
	char	**tmp;
	int		i;

	if (buf == NULL)
		return ;
	i = 0;
	while (data->map != NULL && data->map[i])
		i++;
	tmp = NULL;
	tmp = mymalloc(sizeof(char *) * (i + 2));
	i = 0;
	while (data->map != NULL && data->map[i])
	{
		tmp[i] = ft_strdup(data->map[i]);
		free(data->map[i]);
		i++;
	}
	tmp[i] = buf;
	tmp[i + 1] = NULL;
	data->map_height = i + 1;
	free(data->map);
	data->map = tmp;
}

static void	read_file(char *filename, t_data *data)
{
	char	*buf;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		panic(ERR_MAP_READ);
	buf = get_next_line(fd);
	add_map(buf, data);
	while (buf != NULL)
	{
		buf = get_next_line(fd);
		add_map(buf, data);
	}
	if (data->map == NULL)
		panic(ERR_MAP_EMPTY);
}

static void	check_ber(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		panic(ERR_ARG_BER);
	if (filename[len - 1] != 'r')
		panic(ERR_ARG_BER);
	if (filename[len - 2] != 'e')
		panic(ERR_ARG_BER);
	if (filename[len - 3] != 'b')
		panic(ERR_ARG_BER);
	if (filename[len - 4] != '.')
		panic(ERR_ARG_BER);
}

static void	check_args(int argc, char *argv[])
{
	if (argc != 2)
		panic(ERR_ARG);
	if (argv[1] == NULL || argv[1][0] == '\0')
		panic(ERR_ARG);
	check_ber(argv[1]);
}

void	parsing(int argc, char *argv[], t_data *data)
{
	check_args(argc, argv);
	read_file(argv[1], data);
}
