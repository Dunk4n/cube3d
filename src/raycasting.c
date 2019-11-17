/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:07:47 by niduches          #+#    #+#             */
/*   Updated: 2019/11/17 18:34:57 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cube3d.h"

t_vec2f	calculate_step(t_map *map, t_vec2f ray_dir, t_vec2i *step,
t_vec2f delta_dist)
{
	t_vec2f	side_dist;
	t_vec2i	pos;

	pos = (t_vec2i){(int)map->pos.x, (int)map->pos.y};
	if (ray_dir.x < 0)
	{
		step->x = -1;
		side_dist.x = (map->pos.x - pos.x) * delta_dist.x;
	}
	else
	{
		step->x = 1;
		side_dist.x = (pos.x + 1.0 - map->pos.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step->y = -1;
		side_dist.y = (map->pos.y - pos.y) * delta_dist.y;
	}
	else
	{
		step->y = 1;
		side_dist.y = (pos.y + 1.0 - map->pos.y) * delta_dist.y;
	}
	return (side_dist);
}

enum	raycasting_tab2i
{
	POS, STEP, NB_TAB2I
};

enum	raycasting_tab2f
{
	DELTA_DIST, SIDE_DIST, NB_TAB2F
};

int		search_obstacle(t_map *map, t_vec2f *tab2f, t_vec2i *tab2i, int *side)
{
	if (tab2f[SIDE_DIST].x < tab2f[SIDE_DIST].y)
	{
		tab2f[SIDE_DIST].x += tab2f[DELTA_DIST].x;
		tab2i[POS].x += tab2i[STEP].x;
		*side = 0;
	}
	else
	{
		tab2f[SIDE_DIST].y += tab2f[DELTA_DIST].y;
		tab2i[POS].y += tab2i[STEP].y;
		*side = 1;
	}
	return (map->map[tab2i[POS].y][tab2i[POS].x] == '1');
}

double	get_hit(t_map *map, t_vec2f ray_dir, int *side)
{
	int		hit;
	t_vec2i tab2i[2];
	t_vec2f tab2f[2];

	hit = 0;
	tab2i[POS] = (t_vec2i){(int)map->pos.x, (int)map->pos.y};
	tab2f[DELTA_DIST] = (t_vec2f){ABS(1 / ray_dir.x), ABS(1 / ray_dir.y)};
	tab2f[SIDE_DIST] = calculate_step(map, ray_dir, tab2i + STEP,
tab2f[DELTA_DIST]);
	while (hit == 0)
		hit = search_obstacle(map, tab2f, tab2i, side);
	if (*side == 0)
		return ((tab2i[POS].x - map->pos.x +
					(1 - tab2i[STEP].x) / 2) / ray_dir.x);
	return ((tab2i[POS].y - map->pos.y + (1 - tab2i[STEP].y) / 2) / ray_dir.y);
}

double	get_ray_dir(t_map *map, int x, t_vec2f *ray_dir, int *side)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (double)map->res.x - 1.0;
	ray_dir->x = map->dir.x + map->plane.x * camera_x;
	ray_dir->y = map->dir.y + map->plane.y * camera_x;
	return (get_hit(map, *ray_dir, side));
}

void	get_draw_size(t_map *map, t_vec3i *draw, t_vec3i *tex, double per_wall_dist)
{
	tex->z = (int)(map->res.y / per_wall_dist);
	draw->x = -tex->z / 2 + map->res.y / 2;
	if (draw->x < 0)
		draw->x = 0;
	draw->y = tex->z / 2 + map->res.y / 2;
	if (draw->y >= map->res.y)
		draw->y = map->res.y - 1;
}

void	get_wall(t_map *map, int x, t_vec3i *draw, t_vec3i *tex)
{
	double	per_wall_dist;
	double	wall_x;
	t_vec2f	ray_dir;
	int		side;

	per_wall_dist = get_ray_dir(map, x, &ray_dir, &side);
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
		color = ((int*)map->tex[tex.y].data)[tex.x +
(tex_y * map->tex[tex.y].size.x)];
		((int*)img->data)[draw.z + (y * img->size_line)] = color;
		y++;
	}
}

void	raycasting(t_map *map, t_tex *img)
{
	int		x;
	t_vec3i draw;
	t_vec3i tex;

	x = 0;
	while (x < map->res.x)
	{
		get_wall(map, x, &draw, &tex);
		draw.z = x;
		draw_vline_tex(map, img, draw, tex);
		//draw_vertical_line(img, x, , 0x00ff0000);
		//draw_vertical_line(img, x, , 0x00ff0000);
		x++;
	}
}
