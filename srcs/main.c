#include "so_long.h"

// memset test erase after DIS
// call mymemset or bzero to init my data structs!
#include <string.h>

void	panic(t_error err_code)
// TODO change printf here!
// putstr?
{
	if (err_code == ERR_MALLOC)
		printf("Error : out of memory ... exiting\n");
	else if (err_code == ERR_MAP_READ)
		printf("Error : cannot read map ... exiting\n");
	else if (err_code == ERR_MAP_OPEN)
		printf("Error : map is not closed... exiting\n");
	else if (err_code == ERR_MAP_RECT)
		printf("Error : map is not rectangle... exiting\n");
	else if (err_code == ERR_MAP_NO_PLAY)
		printf("Error : no player in map... exiting\n");
	else if (err_code == ERR_MAP_MANY_PLAY)
		printf("Error : too many players in map... exiting\n");
	else if (err_code == ERR_MAP_COLL)
		printf("Error : no collectible in map... exiting\n");
	else if (err_code == ERR_MAP_EXIT)
		printf("Error : no exit in map... exiting\n");
	else if (err_code == ERR_MAP_WCHAR)
		printf("Error : no valid char in map... exiting\n");
	else if (err_code == ERR_MAP_EMPTY)
		printf("Error : map is empty... exiting\n");
	else if (err_code == ERR_ARG)
		printf("Error : no valid argument received... exiting\n");
	else if (err_code == ERR_ARG_BER)
		printf("Error : map doesnt end with '.ber'... exiting\n");
	else
		printf("Unknown Error ... exiting\n");
	exit(ERR);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *) s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

// TODO get all of the struct into one big struct data
// do get_data() with static data, and create init data with memset all to 0

t_check	*get_check(void)
{
	static t_check	check;

	//memset(&check, '\0', sizeof(t_check));
	return (&check);
}

t_map	*get_map(void)
{
	static t_map	map;

	//memset(&map, '\0', sizeof(t_map));
	return (&map);
}

t_player	*get_player(void)
{
	static t_player	player;

	//memset(&map, '\0', sizeof(t_map));
	return (&player);
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

int	open_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		panic(ERR_MAP_READ); // error about args, filename cant be accessed 
	return (fd);
}

void	*mymalloc(size_t size)
{
	void *out;

	out = malloc(size);
	if (out == NULL)
	{
		// call exit ERR MALL here!
		panic(ERR_MALLOC);
	}
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
// cut in more than 1 func
// test for more randon rectangle errors
void	check_map(char **map)
{
	int		i;
	int		o;
	t_check	*check;

	if (get_map()->map == NULL)
		panic(ERR_MAP_EMPTY); //map empty
	i = 0;
	check = get_check();
	check->player = 0;
	get_map()->x = ft_strlen(map[i]);
	if (get_map()->x < 3 || get_map()->y < 3)
			panic(ERR_MAP_RECT);
	if (get_map()->x == get_map()->y)
			panic(ERR_MAP_RECT);
	while (map[i])
	{
		o = 0;
		if (get_map()->x != ft_strlen(map[i]))
			panic(ERR_MAP_RECT);
		while (map[i][o])
		{
			if (map[i][o] == '0' || map[i][o] == '1' || map[i][o] == 'C'
				|| map[i][o] == 'E' || map[i][o] == 'P')
			{
				if (map[i][o] == 'P')
				{
					if (check->player == 1)
						panic(ERR_MAP_MANY_PLAY);
					check->player = 1;
				}
				if (map[i][o] == 'E')
					check->exit = 1;
				if (map[i][o] == 'C')
					check->collec = 1;
			}
			else
				panic(ERR_MAP_WCHAR);
			o++;
		}
		i++;
	}
	if (check->player == 0)
		panic(ERR_MAP_MANY_PLAY);
	if (check->collec == 0)
		panic(ERR_MAP_COLL);
	if (check->exit == 0)
		panic(ERR_MAP_EXIT);
}

// TODO change func name, this gets player coords into player struct only, for now
// maybe just put it into parsing directly
// maybe no need to add player pro cos check map already done
void	get_data_map(char **map)
{
	int	i;
	int	o;

	if (map == NULL)
		panic(ERR_MAP_EMPTY);
	i = 0;
	while (map[i])
	{
		o = 0;
		while (map[i][o])
		{
			if (map[i][o] == 'P')
			{
				get_player()->y = i;
				get_player()->x = o;
				// erased 'P' of map after getting coords like cub3d, is dis useful???
				map[i][o] = '0';
			}
			o++;
		}
		i++;
	}
	printf("%f %f\n", get_player()->y, get_player()->x);
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
	map->y = 0; // if prob with y then erase dis
	read_file(fd, map);
	check_map(map->map);
	get_data_map(map->map);
	// get map into memory // done
	// check if map closed
	// check if only 1 player // done
	// check if not random chars // done
	// check if 1 exit 1 collectible, starting position // done
	// check if map is rectangular //done
}

void	check_filename(int argc, char *argv[])
{
	if (argc != 2)
		panic(ERR_ARG);
	if (argv[1][0] == '\0')
		panic(ERR_ARG);
	check_ber(argv[1]);
}

int	main(int argc, char *argv[])
{
	//char *filename;

	(void) argc;
	(void) argv;
	//check_filename(argc, argv);
	//filename = argv[1];
	//parsing(filename);
	int	c = 0;
	int	len = 1000000;
			//2147483648
	int	i = 0;
	int q = len / 4;
	int	o = len / 2;
	int	*arr = mymalloc(sizeof(int) * len);

	printf("%d %d %d\n", o, len, q);
	while (arr != NULL && i < (len / 2))
	{
		arr[i] = 10;
		//write(1,"X",1);
		arr[o] = 30;
		printf("%d %d\n", i, o);
		o++;
		i++;
		c++;
	}
	printf("%d\n", c);
	/*
	c = 0;
	while (c < len)
	{
		printf("%d\n", arr[c]);
		c++;
	}
	*/
	(void) arr;
	return (0);
}
