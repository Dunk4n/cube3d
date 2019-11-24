/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:07:47 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 16:36:15 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

t_vec2f			get_floor_wall(t_map *map)
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

void			display_floor(t_map *map, t_tex *img, t_vec3i draw)
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

void			get_dist(t_map *map, double *dist, t_vec3i draw)
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

void			raycasting(t_map *map, t_tex *img)
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
