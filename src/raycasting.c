/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:07:47 by niduches          #+#    #+#             */
/*   Updated: 2019/11/16 21:31:23 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_vec2i	get_wall_pos(t_map *map, int x, double *per_wall_dist)
{
	double	camera_x;
	t_vec2i	pos;
	t_vec2f	ray_dir;
	t_vec2f	side_dist;
	t_vec2f	delta_dist;
	t_vec2i step;
	int		hit;
	int		side;

	hit = 0;
	camera_x = 2.0 * (double)x / (double)map->res.x - 1.0;
	ray_dir.x = map->dir.x + map->plane.x * camera_x;
	ray_dir.y = map->dir.y + map->plane.y * camera_x;
	pos.x = (int)map->pos.x;
	pos.y = (int)map->pos.y;

	delta_dist.x = ABS(1 / ray_dir.x);
	delta_dist.y = ABS(1 / ray_dir.y);
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (map->pos.x - pos.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (pos.x + 1.0 - map->pos.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (map->pos.y - pos.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (pos.y + 1.0 - map->pos.y) * delta_dist.y;
	}
	while (hit == 0)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			pos.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			pos.y += step.y;
			side = 1;
		}
		if (map->map[pos.y][pos.x] == '1')
			hit = 1;
	}
	if (side == 0)
		*per_wall_dist = (pos.x - map->pos.x + (1 - step.x) / 2) / ray_dir.x;
	else
		*per_wall_dist = (pos.y - map->pos.y + (1 - step.y) / 2) / ray_dir.y;
	return (pos);
}

void	raycasting(t_map *map, t_tex *img)
{
	int		x;
	int		line_height;
	double	per_wall_dist;
	t_vec2i	pos;
	t_vec2i draw;
	int		tab[] = {0x00ff0000, 0x0000ff00, 0x000000ff, 0x00ffff00, 0x00ff00ff, 0x0000ffff, 0x00ffffff};

	x = 0;
	while (x < map->res.x)
	{
		pos = get_wall_pos(map, x, &per_wall_dist);
		line_height = (int)(map->res.y / per_wall_dist);
		draw.x = -line_height / 2 + map->res.y / 2;
		if (draw.x < 0)
			draw.x = 0;
		draw.y = line_height / 2 + map->res.y / 2;
		if (draw.y >= map->res.y)
			draw.y = map->res.y - 1;
		draw_vertical_line(img, x, (t_vec2i){0, draw.x}, map->roof.color);
		draw_vertical_line(img, x, draw, tab[(pos.x + pos.y) % (sizeof(tab) / 4)]);
		draw_vertical_line(img, x, (t_vec2i){draw.y, map->res.y}, map->floor.color);
		x++;
	}
}
