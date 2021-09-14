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

typedef struct		s_text_img
{
	// im even using dis bs? look n erase
	// just changed int *addr to char *addr is dis good?
	int				wid;
	int				hei;
	int				bpp;
	int				size;
	int				endian;
	void			*img;
	char			*addr;
}					t_text_img;

typedef struct		s_mlx
{
	void			*mlx;
	void			*mlx_win;
	long			mlx_wid;
	long			mlx_hei;
	t_text_img		up_text;
	t_text_img		do_text;
	t_text_img		le_text;
	t_text_img		ri_text;
}					t_mlx;

typedef struct		s_img
{
	// im even using dis bs? look n erase
	void			*img;
	int				*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_map
{
	// when i create data i erase t_map
	// send x,y directly to t_mlx
	// send **map directly to data
	// x,y long ?
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
	// double needed? not like c3d that needed +0.5 in coords
	double	x;
	double	y;
}			t_player;
