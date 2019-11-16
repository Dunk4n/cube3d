/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:53:13 by niduches          #+#    #+#             */
/*   Updated: 2019/11/16 19:36:22 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d.h"

void	clear_img(t_tex *img)
{
	int	i;
	int	j;
	int	size;

//	printf("%d, %d, %d\n", img->size_line, img->size.y, img->size_line * img->size.y);
//	size = img->size_line * img->size.y;
	i = 0;
	while (i < img->size.y)
	{
		j = 0;
		while (j < img->size.x)
		{
			((int*)img->data)[j + (i * img->size_line)] = 0;
			j++;
		}
		i++;
	}
}

int		display(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	clear_img(&game->img);
	raycasting(&game->map, &game->img);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.tex, 0, 0);
	//usleep(500000);
	return (0);
}
