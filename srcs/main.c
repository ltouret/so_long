#include "so_long.h"

// TODO change t_data for t_img
// TODO add define with 32 and use it? when creating map and all
// TODO if they change my textures code breaks... as they are not 32 x,y

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	load_textures(t_data *data)
{
	// open textures
	data->mlx.up_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
		"./textures/up.xpm", &data->mlx.up_text.wid, &data->mlx.up_text.hei);
	data->mlx.do_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
		"./textures/down.xpm", &data->mlx.do_text.wid, &data->mlx.do_text.hei);
	data->mlx.le_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
		"./textures/left.xpm", &data->mlx.le_text.wid, &data->mlx.le_text.hei);
	data->mlx.ri_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
		"./textures/right.xpm", &data->mlx.ri_text.wid, &data->mlx.ri_text.hei);
	data->mlx.co_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
		"./textures/coll.xpm", &data->mlx.ri_text.wid, &data->mlx.ri_text.hei);
	data->mlx.ex_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
		"./textures/exit.xpm", &data->mlx.ri_text.wid, &data->mlx.ri_text.hei);
	data->mlx.wa_text.img = mlx_xpm_file_to_image(data->mlx.mlx,
		"./textures/wall.xpm", &data->mlx.ri_text.wid, &data->mlx.ri_text.hei);
	if (data->mlx.up_text.img == NULL
		|| data->mlx.do_text.img == NULL
		|| data->mlx.le_text.img == NULL || data->mlx.ri_text.img == NULL
		|| data->mlx.co_text.img == NULL || data->mlx.ex_text.img == NULL
		|| data->mlx.wa_text.img == NULL)
		panic(ERR_TEXT);
}

void	load_textures_addr1(t_data *data)
{
	data->mlx.up_text.addr = mlx_get_data_addr(data->mlx.up_text.img,
		&data->mlx.up_text.bpp, &data->mlx.up_text.line_length,
		&data->mlx.up_text.endian);
	data->mlx.do_text.addr = mlx_get_data_addr(data->mlx.do_text.img,
		&data->mlx.do_text.bpp, &data->mlx.do_text.line_length,
		&data->mlx.do_text.endian);
	data->mlx.le_text.addr = mlx_get_data_addr(data->mlx.le_text.img,
		&data->mlx.le_text.bpp, &data->mlx.le_text.line_length,
		&data->mlx.le_text.endian);
	data->mlx.ri_text.addr = mlx_get_data_addr(data->mlx.ri_text.img,
		&data->mlx.ri_text.bpp, &data->mlx.ri_text.line_length,
		&data->mlx.ri_text.endian);
	data->mlx.ex_text.addr = mlx_get_data_addr(data->mlx.ex_text.img,
		&data->mlx.ex_text.bpp, &data->mlx.ex_text.line_length,
		&data->mlx.ex_text.endian);
	data->mlx.wa_text.addr = mlx_get_data_addr(data->mlx.wa_text.img,
		&data->mlx.wa_text.bpp, &data->mlx.wa_text.line_length,
		&data->mlx.wa_text.endian);
	data->mlx.co_text.addr = mlx_get_data_addr(data->mlx.co_text.img,
		&data->mlx.co_text.bpp, &data->mlx.co_text.line_length,
		&data->mlx.co_text.endian);
}

void	img_screen(t_text_img *img, t_img *mimg, int x, int y)
{
	char	*dst;
	int		text[2];
	int		new_coord[2];
	int		oy;

	ft_bzero(&text, sizeof(text));
	oy = y;
	new_coord[0] = x + 32;
	new_coord[1] = y + 32;

	while (x < new_coord[0])
	{
		y = oy;
		text[1] = 0;
		while (y < new_coord[1])
		{
			dst = img->addr + (text[1]
				* img->line_length + text[0]
				* (img->bpp / 8));
			if (*(unsigned int *)dst != 0xff000000)
				my_mlx_pixel_put(mimg, x, y, *((unsigned int *)dst));
			text[1]++;
			y++;
		}
		text[0]++;
		x++;
	}
	//mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, mimg->img, 0, 0);
}

int	keypress(int key, t_data *data)
{
	(void) data;
	printf("%d\n", key);
	if (key == 65307)
	{
		// call exit esc key pressed
		panic(-1);
	}
	else if (key < 280)
		data->keycode[key] = 1;
	return (OK);
}

int	keyrelease(int key, t_data *data)
{
	(void) data;
	//printf("%d\n", key);
	if (key < 280)
		data->keycode[key] = 0;
	return (OK);
}

void	mlx_stuff(t_data *data)
{
	// mlx setup - mlx init
	// added x,y for mlx

	//TODO check if mlx init != NULL or exit program and return ERR_MLX
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_wid = data->map_width * 32;
	data->mlx.mlx_hei = data->map_height * 32;
	load_textures(data);
	load_textures_addr1(data);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->mlx.mlx_wid, data->mlx.mlx_hei, "so_long");

	// Drawing floor
	int	x = 0;
	int	y = 0;
	t_img mimg;

	mimg.img = mlx_new_image(data->mlx.mlx, data->mlx.mlx_wid, data->mlx.mlx_hei);
	mimg.addr = mlx_get_data_addr(mimg.img, &mimg.bpp, &mimg.line_length,
								&mimg.endian);

	while (x < data->mlx.mlx_wid)
	{
		y = 0;
		while (y < data->mlx.mlx_hei)
		{
			my_mlx_pixel_put(&mimg, x, y, 0x009cd3db);
			y++;
		}
		x++;
	}
	// end

	// Drawing map
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				img_screen(&data->mlx.wa_text, &mimg, x * 32, y * 32);
			else if (data->map[y][x] == 'C')
				img_screen(&data->mlx.co_text, &mimg, x * 32, y * 32);
			else if (data->map[y][x] == 'E')
				img_screen(&data->mlx.ex_text, &mimg, x * 32, y * 32);
			//else if (data->map[y][x] == 'P')
			//	img_screen(&data->mlx.up_text, &mimg, x * 32, y * 32);
			x++;
		}
		y++;
	}
	// end

	// Drawing player
	//printf("%d %d\n", data->player.x, data->player.y);
	//data->player.x = 1;
	//data->player.y = 1;
	t_text_img	*player;
	if (data->player.dir == 'u')
		player = &data->mlx.up_text;
	else if (data->player.dir == 'd')
		player = &data->mlx.do_text;
	else if (data->player.dir == 'l')
		player = &data->mlx.le_text;
	else if (data->player.dir == 'r')
		player = &data->mlx.ri_text;
	img_screen(player, &mimg, data->player.x * 32, data->player.y * 32);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, mimg.img, 0, 0);

	mlx_mouse_hide(data->mlx.mlx, data->mlx.mlx_win);
	mlx_hook(data->mlx.mlx_win, 2, 1L << 0, keypress, data);
	mlx_hook(data->mlx.mlx_win, 3, 1L << 1, keyrelease, data);
	//mlx_hook(data->mlx.mlx_win, 17, 1L << 17, exit_pro, data);
	mlx_loop_hook(data->mlx.mlx, player_movements, data);
	mlx_loop(data->mlx.mlx);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = get_data();
	parsing(argc, argv, data);
	validate_map(data);
	show_map();
	mlx_stuff(data);

	return (0);
}
