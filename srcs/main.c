/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 23:25:39 by ltouret           #+#    #+#             */
/*   Updated: 2021/09/05 11:23:31 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "gnl/get_next_line.h"

//int	panic(int err)

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	check_ber(char *filename)
{
	// error about args, no .ber, check if enough protection
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		exit (1);
	if (filename[len - 1] != 'r')
		exit (1);
	if (filename[len - 2] != 'e')
		exit (1);
	if (filename[len - 3] != 'b')
		exit (1);
	if (filename[len - 4] != '.')
		exit (1);
}

int	open_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit (1); // error about args, filename cant be accessed 
	return (fd);
}

void	read_file(int fd)
{
	char	buf[4];

	buf[3] = '\0';
	read(fd, buf, 3);
	printf("%s\n", buf);
}

void	parsing(char *filename)
{
	int fd;

	fd = open_file(filename);
	read_file(fd);
	// get map into memory
	// check if map closed
	// check if only 1 player
	// check if not random chars 
	// check if 1 exit 1 collectible, starting position
	// check if map is rectangular
}

void	check_filename(int argc, char *argv[])
{
	if (argc != 2)
		exit (1); // error about args, need 1 max
	if (argv[1][0] == '\0')
		exit (1); // error about args, empty filename
	check_ber(argv[1]);
}

int	main(int argc, char *argv[])
{
	char *filename;

	check_filename(argc, argv);
	filename = argv[1];
	parsing(filename);
	return (0);
}
