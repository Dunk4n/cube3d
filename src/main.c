/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:13:31 by niduches          #+#    #+#             */
/*   Updated: 2019/11/15 12:45:36 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>

typedef union	u_color
{
	unsigned char	ARGB[4];
	unsigned int	color;
}				t_color;

typedef	struct	s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_win;

typedef struct	s_veci2
{
	int	x;
	int	y;
}				t_veci2;


void	draw_square(t_win *win, t_veci2 pos, t_veci2 size, union u_color color, char *img)
{
	int i;
	int j;

	printf("pos x = %d, y = %d\n", pos.x, pos.y);
	printf("size x = %d, y = %d\n", size.x, size.y);
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
//			mlx_pixel_put(win->mlx_ptr, win->win_ptr,
//pos.x + j, pos.y + i, color);
			img[((j) * 4) + (i * 4 * 128)] = color.ARGB[0];
			img[((j) * 4) + (i * 4 * 128) + 1] = color.ARGB[1];
			img[((j) * 4) + (i * 4 * 128) + 2] = color.ARGB[2];
			img[((j) * 4) + (i * 4 * 128) + 3] = 0;
			j++;
		}
		i++;
	}
	printf("x = %d, y = %d, aret = %d\n", pos.x + j, pos.y + i, (((pos.x + j) * 4) + (pos.y + i) * (400)));
}

int		main(void)
{
	t_win			win;
	union u_color	color;

	if (!(win.mlx_ptr = mlx_init()))
		return (0);
	if (!(win.win_ptr = mlx_new_window(win.mlx_ptr, 500, 500, "test 42")))
		return (0);
	void *img = mlx_new_image(win.mlx_ptr, 100, 100);
	if (!img)
		return (0);
	color.ARGB[0] = 0;
	color.ARGB[1] = 0;
	color.ARGB[2] = 255;
	color.ARGB[3] = 0;

	int pixel = 0;
	int line = 0;
	int endian = 0;
	void *data = mlx_get_data_addr(img, &pixel, &line, &endian);

	printf("line = %d\n", line / 4);
	draw_square(&win, (t_veci2){0, 0}, (t_veci2){100, 100}, color, (char*)data);
	printf("AAA\n");
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img, 0, 0);
	printf("b\n");
	mlx_loop(win.mlx_ptr);
	printf("c\n");
	mlx_destroy_window(win.mlx_ptr, win.win_ptr);
	return (0);
}
