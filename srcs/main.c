#include "so_long.h"

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
	t_data	*data;

	data = get_data();
	parsing(argc, argv, data);
	validate_map(data);
	show_map();

	/*
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
	*/

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
