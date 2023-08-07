/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:57:17 by niduches          #+#    #+#             */
/*   Updated: 2019/11/20 19:07:34 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	int	y;
	int	d;
	int	tex_y;
	int color;

	y = draw.x;
	while (y < draw.y)
	{
		d = y * 256 - map->res.y * 128 + tex.z * 128;
		tex_y = ((d * map->tex[tex.y].size.y) / tex.z) / 256;
        if(tex_y >= 0)
            color = ((int*)map->tex[tex.y].data)[((map->tex[tex.y].size.x - 1) - tex.x) + (tex_y * map->tex[tex.y].size.x)];
		((int*)img->data)[draw.z + (y * img->size_line)] = color;
		y++;
	}
}
