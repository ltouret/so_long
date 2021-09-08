#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "gnl/get_next_line.h"

// memset test erase after DIS
// call mymemset to init my data structs!
#include <string.h>

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

typedef struct s_map
{
	char	**map;
	int		x;
	int		y;
}			t_map;

typedef struct s_check
{
	int		player;
	int		exit;
	int		collec;
}			t_check;

t_check	*get_check(void)
{
	static t_check check;

	//memset(&check, '\0', sizeof(t_check));
	return (&check);
}

t_map	*get_map(void)
{
	static t_map map;

	//memset(&map, '\0', sizeof(t_map));
	return (&map);
}

//deprecated erase after being done
void	show_map(void)
{
	int		i;
	char	**map;

	i = 0;
	map = get_map()->map;
	while (map != NULL && map[i])
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
		exit(1); // ERR mall here
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

void	read_file(int fd, t_map *map)
{
	char	*buf;

	buf = get_next_line(fd);
	add_map(buf, map);
	while (buf != NULL)
	{
		buf = get_next_line(fd);
		add_map(buf, map);
	}
	show_map();
	printf("y: %d\n", map->y);
}

//  TODO create player object with coordinates
//  TODO check if map rectangular
// init check!
// if no map segfault! check why!
// cut in more than 1 func
// test for more randon rectangle errors
void	check_map(char **map)
{
	int		i;
	int		o;
	t_check	*check;

	if (get_map()->map == NULL)
		exit(1); // ERR map empty
	i = 0;
	check = get_check();
	check->player = 0;
	get_map()->x = ft_strlen(map[i]);
	if (get_map()->x < 3 || get_map()->y < 3)
			exit (1); // ERR not rectange // ERR if x or y == 2 then map not closed!
	if (get_map()->x == get_map()->y)
			exit (1); // ERR not rectangle
	while (map[i])
	{
		o = 0;
		if (get_map()->x != ft_strlen(map[i]))
			exit (1); // ERR not rectangle
		while (map[i][o])
		{
			if (map[i][o] == '0' || map[i][o] == '1' || map[i][o] == 'C'
				|| map[i][o] == 'E' || map[i][o] == 'P')
			{
				if (map[i][o] == 'P')
				{
					if (check->player == 1)
						exit (1); // ERR too many players
					check->player = 1;
				}
				if (map[i][o] == 'E')
					check->exit = 1;
				if (map[i][o] == 'P')
					check->collec = 1;
			}
			else
				exit(1); // ERR Random char in map
			o++;
		}
		i++;
	}
	if (!check->player || !check->collec || !check->exit)
		exit(1); // ERR missing elem P/C/E
}

void	parsing(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open_file(filename);

	// get init out of here!!!
	map = get_map();
	map->map = NULL;
	map->x = 0;
	map->y = 0; // if pro with y then erase dis
	read_file(fd, map);
	check_map(map->map);
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
