/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:57:17 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 15:26:48 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void	draw_square(t_tex *img, t_vec2i pos, t_vec2i draw, int color)
{
	int		i;
	int		j;
	t_vec2i	len;

	len.y = pos.y + draw.y;
	len.x = pos.x + draw.x;
	i = pos.y;
	while (i < len.y)
	{
		j = pos.x;
		while (j < len.x)
		{
			((int*)img->data)[j + (i * img->size_line)] = color;
			j++;
		}
		i++;
	}
}

void	draw_vertical_line(t_tex *img, int x, t_vec2i draw, int color)
{
	int	i;

	i = draw.x;
	while (i < draw.y)
	{
		((int*)img->data)[x + (i * img->size_line)] = color;
		i++;
	}
}

void	draw_vline_tex(t_map *map, t_tex *img, t_vec3i draw, t_vec3i tex)
{
	int		d;
	int		tex_y;
	t_color	color;
	double	fact;

	if (map->zbuffer[draw.z] > 7)
		return ;
	fact = map->zbuffer[draw.z] / 10 + 0.5;
	if (fact < 0.2)
		fact = 0.2;
	if (fact > 1)
		fact = 1;
	fact = 1 - fact;
	while (draw.x < draw.y)
	{
		d = (draw.x - map->h) * 256 - map->res.y * 128 + tex.z * 128;
		tex_y = ((d * map->tex[tex.y].size.y) / tex.z) / 256;
        if(tex_y >= 0)
            color.color = ((int*)map->tex[tex.y].data)[((map->tex[tex.y].size.x - 1) - tex.x) + (tex_y * map->tex[tex.y].size.x)];
		color.argb[R] *= fact;
		color.argb[G] *= fact;
		color.argb[B] *= fact;
		((int*)img->data)[draw.z + (draw.x++ * img->size_line)] = color.color;
	}
}
