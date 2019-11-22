/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:55:44 by niduches          #+#    #+#             */
/*   Updated: 2019/11/22 21:00:22 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cube3d_bonus.h"

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
	if (tab2i[POS].y < 0 || tab2i[POS].y >= map->nb_line ||
tab2i[POS].x < 0 || tab2i[POS].x >= map->line_size[tab2i[POS].y])
		return (1);
	if (tab2i[POS].x >= map->line_size[tab2i[POS].y - 1] ||
tab2i[POS].x >= map->line_size[tab2i[POS].y + 1])
		return (1);
	return (map->map[tab2i[POS].y][tab2i[POS].x] == '1' ||
map->map[tab2i[POS].y][tab2i[POS].x] == '6');
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
	map->for_floor.pos.x = tab2i[POS].x;
	map->for_floor.pos.y = tab2i[POS].y;
	if (*side == 0)
		return ((tab2i[POS].x - map->pos.x +
					(1 - tab2i[STEP].x) / 2) / ray_dir.x);
	else
		return ((tab2i[POS].y - map->pos.y + (1 - tab2i[STEP].y) / 2) /
ray_dir.y);
}
