#include "so_long.h"

// TODO change t_data for t_img
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

void	img_screen(t_data *data, t_img *mimg, int x, int y)
{
	char	*dst;
	(void) dst;
	int		tx = 0;
	int		ty = 0;
	int		ox = x;
	int		nx = x + 32;
	int		ny = y + 32;

	printf("%d %d\n", x, nx);
	while (y < ny)
	{
		x = ox;
		while (x < nx)
		{
			//dst = data->mlx.up_text.addr + (ty * data->mlx.up_text.line_length + tx * (data->mlx.up_text.bpp / 8));
			//if (*(unsigned int *)dst != 0xff000000)
				//my_mlx_pixel_put(mimg, x, y, *((unsigned int *)dst));
				my_mlx_pixel_put(mimg, x, y, 0x00ff0f00);
			x++;
			tx++;
		}
		ty++;
		y++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, mimg->img, 0, 0);
}

void	mlx_stuff(t_data *data)
{
	// mlx setup

	// added x,y for mlx
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_wid = data->map_width * 32;
	data->mlx.mlx_hei = data->map_height * 32;
	load_textures(data);
	load_textures_addr1(data);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->mlx.mlx_wid, data->mlx.mlx_hei, "so_long");
	//printf("%ld %ld\n", data->mlx.mlx_wid, data->mlx.mlx_hei);


	// testing stuff

	int y = 0;
	int	x = 0;
	t_img mimg;

	mimg.img = mlx_new_image(data->mlx.mlx, data->mlx.mlx_wid, data->mlx.mlx_hei);
	mimg.addr = mlx_get_data_addr(mimg.img, &mimg.bpp, &mimg.line_length,
								&mimg.endian);

	while (y < data->mlx.mlx_hei)
	{
		x = 0;
		while (x < data->mlx.mlx_wid)
		{
			my_mlx_pixel_put(&mimg, x, y, 0x009cd3db);
			x++;
		}
		y++;
	}

	/*
	char	*dst;
	x = 0;
	y = 0;

	while (y < 32)
	{
		x = 0;
		while (x < 32)
		{
			dst = data->mlx.up_text.addr + (y * data->mlx.up_text.line_length + x * (data->mlx.up_text.bpp / 8));
			if (*(unsigned int *)dst != 0xff000000)
				my_mlx_pixel_put(&mimg, x, y, *((unsigned int *)dst));
			x++;
		}
		y++;
	}
	*/
	//mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, mimg.img, 0, 0);
	img_screen(data, &mimg, 10, 10);

	while (1);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = get_data();
	parsing(argc, argv, data);
	validate_map(data);
	//show_map();
	mlx_stuff(data);

	/*
	void	*mlx;
	void	*mlx_win;
	char	*relative_path = "./textures/up.xpm";
	int		img_width;
	int		img_height;
	t_data	img;
	t_data	mimg;

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
