#include "so_long.h"

// check if this is still needed after breaking check_map in funcs
static t_check	*get_check(void)
{
	// stop using this, just create check in check map and then bye
	static t_check	check;

	//memset(&check, '\0', sizeof(t_check));
	return (&check);
}

//  TODO create player object with coordinates
//  TODO check if map rectangular
// init check!
// cut in more than 1 func
// test for more randon rectangle errors
static void	check_map(t_data *data)
{
	int		i;
	int		o;
	t_check	*check;

	i = 0;
	check = get_check();
	ft_bzero(check, sizeof(t_check));
	data->map_width = ft_strlen(data->map[0]);
	if (data->map_width < 3 || data->map_height < 3)
		panic(ERR_MAP_RECT);
	if (data->map_width == data->map_height)
		panic(ERR_MAP_RECT);
	while (data->map[i])
	{
		o = 0;
		if (data->map_width != ft_strlen(data->map[i]))
			panic(ERR_MAP_RECT);
		while (data->map[i][o])
		{
			if (data->map[i][o] == '0' || data->map[i][o] == '1' || data->map[i][o] == 'C'
				|| data->map[i][o] == 'E' || data->map[i][o] == 'P')
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
			if (data->map[i][o] == 'P')
			{
				data->player.x = o;
				data->player.y = i;
				// TODO idk if i init this here?
				data->player.dir = 'u';
				// erased 'P' of map after getting coords like cub3d, is dis useful???
				data->map[i][o] = '0';
				break;
			}
			o++;
		}
		i++;
	}
	//printf("%f %f\n", data->player.y, data->player.x);
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
