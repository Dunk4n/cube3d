/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:52:23 by niduches          #+#    #+#             */
/*   Updated: 2019/11/19 14:25:31 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cube3d.h"

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
	draw->x = -tex->z / 2 + map->res.y / 2;
	if (draw->x < 0)
		draw->x = 0;
	draw->y = tex->z / 2 + map->res.y / 2;
	if (draw->y >= map->res.y)
		draw->y = map->res.y;
}

void	get_wall(t_map *map, int x, t_vec3i *draw, t_vec3i *tex)
{
	double	per_wall_dist;
	double	wall_x;
	t_vec2f	ray_dir;
	int		side;

	per_wall_dist = get_ray_dir(map, x, &ray_dir, &side);
	map->zbuffer[x] = per_wall_dist;
	get_draw_size(map, draw, tex, per_wall_dist);
	wall_x = ((side == 0) ? map->pos.y + per_wall_dist * ray_dir.y :
map->pos.x + per_wall_dist * ray_dir.x);
	wall_x -= floor(wall_x);
	tex->y = !side;
	tex->x = (int)(wall_x * (double)map->tex[tex->y].size.y);
	if (side == 0 && ray_dir.x > 0)
	{
		tex->y += 2;
		tex->x = map->tex[tex->y].size.x - tex->x - 1;
	}
	if (side == 1 && ray_dir.y < 0)
	{
		tex->y += 2;
		tex->x = map->tex[tex->y].size.x - tex->x - 1;
	}
}
