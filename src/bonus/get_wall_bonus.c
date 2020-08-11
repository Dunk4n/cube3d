/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:52:23 by niduches          #+#    #+#             */
/*   Updated: 2019/11/23 16:28:14 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cube3d_bonus.h"

double	get_ray_dir(t_map *map, int x, t_vec2f *ray_dir, int *side)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (double)map->res.x - 1.0;
	ray_dir->x = map->dir.x + map->plane.x * camera_x;
	ray_dir->y = map->dir.y + map->plane.y * camera_x;
	return (get_hit(map, *ray_dir, side));
}

void	get_draw_size(t_map *map, t_vec3i *draw, t_vec3i *tex,
double per_wall_dist)
{
	tex->z = (int)(map->res.y / per_wall_dist);
	draw->x = -tex->z / 2 + map->height_d2 + map->h;
	if (draw->x < 0)
		draw->x = 0;
	draw->y = tex->z / 2 + map->height_d2 + map->h;
	if (draw->y >= map->res.y)
		draw->y = map->res.y;
}

void	get_wall(t_map *map, int x, t_vec3i *draw, t_vec3i *tex)
{
	map->for_floor.per_wall_dist = get_ray_dir(map, x, &map->for_floor.ray_dir,
&map->for_floor.side);
	map->zbuffer[x] = map->for_floor.per_wall_dist;
	get_draw_size(map, draw, tex, map->for_floor.per_wall_dist);
	map->for_floor.wall_x = ((map->for_floor.side == 0) ? map->pos.y +
map->for_floor.per_wall_dist * map->for_floor.ray_dir.y :
map->pos.x + map->for_floor.per_wall_dist * map->for_floor.ray_dir.x);
	map->for_floor.wall_x -= floor(map->for_floor.wall_x);
	tex->y = !map->for_floor.side;
	tex->x = (int)(map->for_floor.wall_x * (double)map->tex[tex->y].size.y);
	if (map->for_floor.side == 0 && map->for_floor.ray_dir.x > 0)
	{
		tex->y += 2;
		tex->x = map->tex[tex->y].size.x - tex->x - 1;
	}
	if (map->for_floor.side == 1 && map->for_floor.ray_dir.y < 0)
	{
		tex->y += 2;
		tex->x = map->tex[tex->y].size.x - tex->x - 1;
	}
}
