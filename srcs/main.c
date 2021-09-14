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
		printf("Error : cannot read map file... exiting\n");
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
	// TODO maybe add more than one p[i]
	// so it bzeros faster!
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
	if (map->map == NULL)
		panic(ERR_MAP_EMPTY); //map empty
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
		panic(ERR_MAP_NO_PLAY);
	if (check->collec == 0)
		panic(ERR_MAP_COLL);
	if (check->exit == 0)
		panic(ERR_MAP_EXIT);
}

// TODO change func name, this gets player coords into player struct only, for now
// maybe just put it into parsing directly
// maybe no need to add player pro cos check map already done
// TODO if check_map checks for empty map before get_data_map | check_map_closed
// then no need to add empty map protection
void	get_data_map(char **map)
{
	int	i;
	int	o;

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

void	check_map_closed(char **map)
{
	int	i;
	int	o;

	i = 0;
	while (map[i])
	{
		o = 0;
		while (map[i][o])
		{
			if ((i == 0 || i == get_map()->y - 1)
				|| (o == 0 || o == get_map()->x - 1))
			{
				if (map[i][o] != '1')
					panic(ERR_MAP_OPEN);
			}
			o++;
		}
		i++;
	}
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
	check_map_closed(map->map);
}

void	check_filename(int argc, char *argv[])
{
	if (argc != 2)
		panic(ERR_ARG);
	if (argv[1][0] == '\0')
		panic(ERR_ARG);
	check_ber(argv[1]);
}

/*
// TODO change t_data for t_img
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
*/

int	main(int argc, char *argv[])
{
	char	*filename;
	t_mlx	mlx;

	ft_bzero(&mlx, sizeof(mlx));
	check_filename(argc, argv);
	filename = argv[1];
	parsing(filename);

	// mlx setup

	// added x,y for mlx
	mlx.mlx_wid = get_map()->x * 32;
	mlx.mlx_hei = get_map()->y * 32;
	//printf("%ld %ld\n", mlx.mlx_wid, mlx.mlx_hei);

	// open textures
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.mlx_wid, mlx.mlx_hei, "so_long");
	mlx.up_text.img = mlx_xpm_file_to_image(mlx.mlx, "./textures/up.xpm", &mlx.up_text.wid, &mlx.up_text.hei);
	mlx.do_text.img = mlx_xpm_file_to_image(mlx.mlx, "./textures/down.xpm", &mlx.do_text.wid, &mlx.do_text.hei);
	mlx.le_text.img = mlx_xpm_file_to_image(mlx.mlx, "./textures/left.xpm", &mlx.le_text.wid, &mlx.le_text.hei);
	mlx.ri_text.img = mlx_xpm_file_to_image(mlx.mlx, "./textures/right.xpm", &mlx.ri_text.wid, &mlx.ri_text.hei);
	if (mlx.up_text.img == NULL)
		write(1,"YH\n", 3);
	if (mlx.do_text.img == NULL)
		write(1,"YH\n", 3);
	if (mlx.le_text.img == NULL)
		write(1,"YH\n", 3);
	if (mlx.ri_text.img == NULL)
		write(1,"YH\n", 3);

	while (1);

	/*
	void	*mlx;
	void	*mlx_win;
	char	*relative_path = "./textures/up.xpm";
	int		img_width;
	int		img_height;
	t_data	img;
	t_data	mimg;

	mlx = mlx_init();
	img.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	if (img.img == NULL)
		write(1,"X",1);
	printf("x %d y %d line %d\n", img_width, img_height, img.line_length);
	mlx_win = mlx_new_window(mlx, 640, 480, "Hello world!");
	mimg.img = mlx_new_image(mlx, 640, 480);
	mimg.addr = mlx_get_data_addr(mimg.img, &mimg.bits_per_pixel, &mimg.line_length,
								&mimg.endian);
	int y = 0;
	int	x = 0;
	while (y < 480)
	{
		x = 0;
		while (x < 640)
		{
			my_mlx_pixel_put(&mimg, x, y, 0x009cd3db);
			if ((((unsigned int *)img.addr)[0] != 0xff000000))
				printf("%x\n", ((int *)img.addr)[1]);
			x++;
		}
		y++;
	}
	y = 0;
	x = 0;
	// TODO transform dis to use my pixel put!
	while (x < 1024)
	{
		if (((unsigned int *)img.addr)[x] != 0xff000000)
			((unsigned int *)mimg.addr)[y] = ((unsigned int *)img.addr)[x];
		x++;
		y++;
		if (x % 32 == 0)
		{
			while (y % 640 != 0)
				y++;
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, mimg.img, 0, 0);
	while (1);
	*/
	return (0);
}
