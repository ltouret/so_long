#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"
#include "keys.h"
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
	ERR_ARG_BER,
	ERR_TEXT
}					t_error;

typedef struct		s_text_img
{
	// im even using dis bs? look n erase
	// just changed int *addr to char *addr is dis good?
	int				wid;
	int				hei;
	int				bpp;
	int				line_length;
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
	t_text_img		ex_text;
	t_text_img		wa_text;
	t_text_img		co_text;
}					t_mlx;

typedef struct		s_img
{
	// im even using dis bs? look n erase
	// same as b4 do i use int or char for addr?
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_check
{
	int		player;
	int		exit;
	int		collec;
}			t_check;

typedef struct s_player
{
	// double needed? not like c3d that needed +0.5 in coords
	int		x;
	int		y;
	char	dir;
}			t_player;

typedef struct		s_data
{
	t_mlx			mlx;
	t_player		player;
	int				map_width;
	int				map_height;
	char			**map;
	int				keys[280];
	int				init;
}					t_data;

void	validate_map(t_data *data);
void	parsing(int argc, char *argv[], t_data *data);
// errors
void	panic(t_error err_code);
// utils
void	ft_bzero(void *s, size_t n);
void	*mymalloc(size_t size);
char	*ft_strdup(char *str);
t_data	*get_data(void);
void	show_map(void);

#endif
