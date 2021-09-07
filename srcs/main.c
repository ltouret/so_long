#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "gnl/get_next_line.h"

//int	panic(int err)

/*
int	ft_strlen(char *str)
>{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
*/

typedef	struct s_map
{
	char	**map;
	int		x;
	int		y;
	int		player;
	int		exit;
	int		collec;
}			t_map;

t_map	*get_map(void)
{
	static t_map map;
	return (&map);
}

//deprecated erase after being done
void	show_map(void)
{
	int		i;
	char	**map;

	i = 0;
	map = get_map()->map;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
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

void	*mymalloc(int size)
{
	void *out;

	out = malloc(size);
	if (out == NULL)
	{
		// call exit ERR MALL here!
		return (NULL);
	}
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

void	add_map(char *buf, t_map *map)
{
	char	**tmp;
	int		i;

	if (buf == NULL)
		return ;
	i = 0;
	while (map->map != NULL && map->map[i])
		i++;
	tmp = NULL;
	tmp = mymalloc(sizeof(char *) * (i + 2));
	i = 0;
	while (map->map != NULL && map->map[i])
	{
		tmp[i] = ft_strdup(map->map[i]);
		free(map->map[i]);
		i++;
	}
	tmp[i] = buf;
	tmp[i + 1] = NULL;
	map->y = i + 1;
	free(map->map);
	map->map = tmp;
}

void	read_file(int fd)
{
	char	*buf;
	t_map	*map;

	//get init out of here!!!
	// get the bools player and all into their own struct boolean to check
	map = get_map();
	map->map = NULL;
	map->x = 0;
	buf = "";
	while (buf != NULL)
	{
		buf = get_next_line(fd);
		add_map(buf, map);
	}
	show_map();
	printf("%d\n", map->y);
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
