/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:07:47 by niduches          #+#    #+#             */
/*   Updated: 2019/11/22 16:58:36 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

t_vec2f	get_floor_wall(t_map *map)
{
	t_vec2f	floor_wall;

	if (map->for_floor.side == 0 && map->for_floor.ray_dir.x > 0)
	{
		floor_wall.x = map->for_floor.pos.x;
		floor_wall.y = map->for_floor.pos.y + map->for_floor.wall_x;
	}
	else if (map->for_floor.side == 0 && map->for_floor.ray_dir.x < 0)
	{
		floor_wall.x = map->for_floor.pos.x + 1.0;
		floor_wall.y = map->for_floor.pos.y + map->for_floor.wall_x;
	}
	else if (map->for_floor.side == 1 && map->for_floor.ray_dir.y > 0)
	{
		floor_wall.x = map->for_floor.pos.x + map->for_floor.wall_x;
		floor_wall.y = map->for_floor.pos.y;
	}
	else
	{
		floor_wall.x = map->for_floor.pos.x + map->for_floor.wall_x;
		floor_wall.y = map->for_floor.pos.y + 1.0;
	}
	return (floor_wall);
}

void	draw_floor(t_map *map, t_tex *img, t_vec2f *floor_wall, t_vec3i draw)
{
	double	current_dist;
	double	weight;
	t_vec2f	current_floor;
	t_vec2i	floor_tex1;
	t_vec2i	floor_tex2;
	t_color	color;
	double	fact;

	current_dist = map->dist[draw.x - map->height_d2];
	if (current_dist > 7)
		return ;
	weight = (current_dist) * (map->for_floor.per_wall_dist);
	current_floor.x = weight * floor_wall->x + (1.0 - weight) * map->pos.x;
	current_floor.y = weight * floor_wall->y + (1.0 - weight) * map->pos.y;
	floor_tex1.x = (int)(current_floor.x * map->tex[F].size.x) % map->tex[F].size_int.x;
	floor_tex1.y = (int)(current_floor.y * map->tex[F].size.y) % map->tex[F].size_int.y;
	floor_tex2.x = (int)(current_floor.x * map->tex[C].size.x) % map->tex[C].size_int.x;
	floor_tex2.y = (int)(current_floor.y * map->tex[C].size.y) % map->tex[C].size_int.y;

	fact = current_dist / 5;
	if (fact > 1)
		fact = 1;
	fact = 1 - fact;
	color.color = ((int*)map->tex[F].data)[floor_tex1.x + (floor_tex1.y * map->tex[F].size_line)];
	color.argb[R] *= fact;
	color.argb[G] *= fact;
	color.argb[B] *= fact;
	((int*)img->data)[draw.z + (draw.x * img->size_line)] = color.color;
	color.color = ((int*)map->tex[C].data)[floor_tex2.x + (floor_tex2.y * map->tex[C].size_line)];
	color.argb[R] *= fact;
	color.argb[G] *= fact;
	color.argb[B] *= fact;
	((int*)img->data)[draw.z + ((map->res.y - draw.x) * img->size_line)] = color.color;
}

void	display_floor(t_map *map, t_tex *img, t_vec3i draw)
{
	t_vec2f	floor_wall;

	floor_wall = get_floor_wall(map);
	if (draw.y < 0)
		draw.y = map->res.y;
	draw.x = draw.y;
	while (draw.x < map->res.y)
	{
		draw_floor(map, img, &floor_wall, draw);
		draw.x++;
	}
}

void	get_dist(t_map *map, double *dist, t_vec3i draw)
{
	int	i;

	if (draw.y < 0)
		draw.y = map->res.y;
	draw.x = map->height_d2;
	i = 0;
	while (draw.x < map->res.y)
	{
		dist[i] = map->res.y / (2.0 * draw.x - map->res.y);
		draw.x++;
		i++;
	}
}

void	raycasting(t_map *map, t_tex *img)
{
	int		x;
	t_vec3i draw;
	t_vec3i tex;

	draw_square(img, (t_vec2i){0, 0},
(t_vec2i){map->res.x, map->res.y}, 0x00000000);
	x = 0;
	while (x < map->res.x)
	{
		get_wall(map, x, &draw, &tex);
		draw.z = x;
		draw_vline_tex(map, img, draw, tex);
		map->for_floor.per_wall_dist = 1 / map->for_floor.per_wall_dist;
		if (map->dist[0] == -1)
			get_dist(map, map->dist, draw);
		if (!map->h)
			display_floor(map, img, draw);
		x++;
	}
	sort_sprite(map);
	display_sprite(map, img);
}
