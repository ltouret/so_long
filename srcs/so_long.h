#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "gnl/get_next_line.h"

typedef enum		e_error
{
	ERR = -1,
	OK = 0,
	ERR_MALLOC,
	ERR_MAP_READ,
	ERR_MAP_OPEN,
	ERR_MAP_RECT,
	ERR_MAP_NO_PLAY,
	ERR_MAP_MANY_PLAY,
	ERR_MAP_COLL,
	ERR_MAP_EXIT,
	ERR_MAP_WCHAR,
	ERR_MAP_EMPTY,
	ERR_ARG,
	ERR_ARG_BER
}					t_error;

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

typedef struct s_player
{
	double	x;
	double	y;
}			t_player;
