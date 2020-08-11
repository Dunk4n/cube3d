/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:34:48 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 16:36:27 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

static int		get_color(t_map *map, t_vec2i floor_tex, int indice,
double fact)
{
	t_color	color;

	color.color = ((int*)map->tex[indice].data)[floor_tex.x + (floor_tex.y *
map->tex[indice].size_line)];
	color.argb[R] *= fact;
	color.argb[G] *= fact;
	color.argb[B] *= fact;
	return (color.color);
}

static t_vec2i	get_pos_tex(t_map *map, t_vec2f current_floor, int indice)
{
	t_vec2i	floor_tex;

	floor_tex.x = (int)(current_floor.x * map->tex[indice].size.x) %
map->tex[indice].size_int.x;
	floor_tex.y = (int)(current_floor.y * map->tex[indice].size.y) %
map->tex[indice].size_int.y;
	return (floor_tex);
}

void			draw_floor(t_map *map, t_tex *img, t_vec2f *floor_wall,
t_vec3i draw)
{
	double	current_dist;
	double	weight;
	t_vec2f	current_floor;
	t_vec2i	floor_tex[2];
	double	fact;

	current_dist = map->dist[draw.x - map->height_d2];
	if (current_dist > 7)
		return ;
	weight = (current_dist) * (map->for_floor.per_wall_dist);
	current_floor.x = weight * floor_wall->x + (1.0 - weight) * map->pos.x;
	current_floor.y = weight * floor_wall->y + (1.0 - weight) * map->pos.y;
	floor_tex[0] = get_pos_tex(map, current_floor, F);
	floor_tex[1] = get_pos_tex(map, current_floor, C);
	fact = current_dist / 5;
	if (fact > 1)
		fact = 1;
	fact = 1 - fact;
	((int*)img->data)[draw.z + (draw.x * img->size_line)] =
get_color(map, floor_tex[0], F, fact);
	((int*)img->data)[draw.z + ((map->res.y - draw.x) * img->size_line)] =
get_color(map, floor_tex[1], C, fact);
}
