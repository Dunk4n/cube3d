/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:54:59 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 17:21:51 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d_bonus.h"

t_vec2f	calculate_step_gun(t_map *map, t_vec2f ray_dir, t_vec2i *step,
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

int		search_obstacle_gun(t_map *map, t_vec2f *tab2f, t_vec2i *tab2i)
{
	char	c;
	int		i;

	if (tab2f[SIDE_DIST].x < tab2f[SIDE_DIST].y)
	{
		tab2f[SIDE_DIST].x += tab2f[DELTA_DIST].x;
		tab2i[POS].x += tab2i[STEP].x;
	}
	else
	{
		tab2f[SIDE_DIST].y += tab2f[DELTA_DIST].y;
		tab2i[POS].y += tab2i[STEP].y;
	}
	if (tab2i[POS].y < 0 || tab2i[POS].y >= map->nb_line ||
tab2i[POS].x < 0 || tab2i[POS].x >= map->line_size[tab2i[POS].y])
		return (1);
	if (tab2i[POS].x >= map->line_size[tab2i[POS].y - 1] ||
tab2i[POS].x >= map->line_size[tab2i[POS].y + 1])
		return (1);
	c = map->map[tab2i[POS].y][tab2i[POS].x];
	i = 0;
	while (CANT_WALK[i])
		if (CANT_WALK[i++] == c)
			return (1);
	return (0);
}

char	*get_pos_hit(t_map *map, int x, t_vec2i *pos)
{
	t_vec2i tab2i[2];
	double	camera_x;
	t_vec2f tab2f[2];
	t_vec2f ray_dir;
	int		hit;

	camera_x = 2.0 * (double)x / (double)map->res.x - 1.0;
	ray_dir.x = map->dir.x + map->plane.x * camera_x;
	ray_dir.y = map->dir.y + map->plane.y * camera_x;
	hit = 0;
	tab2i[POS] = (t_vec2i){pos->x, pos->y};
	tab2f[DELTA_DIST] = (t_vec2f){ABS(1 / ray_dir.x), ABS(1 / ray_dir.y)};
	tab2f[SIDE_DIST] = calculate_step_gun(map, ray_dir, tab2i + STEP,
tab2f[DELTA_DIST]);
	while (hit == 0)
		hit = search_obstacle_gun(map, tab2f, tab2i);
	pos->x = tab2i[POS].x;
	pos->y = tab2i[POS].y;
	return (&map->map[pos->y][pos->x]);
}

void	attack_gun(t_map *map)
{
	t_vec2i		pos;
	t_sprite	*sp;
	char		*c;

	pos.x = (int)map->pos.x;
	pos.y = (int)map->pos.y;
	c = get_pos_hit(map, map->res.x / 2, &pos);
	if (*c != '9')
		return ;
	sp = search_sprite(map, pos.x, pos.y);
	if (sp->tex == MONSTER)
	{
		sp->tmp -= 3;
		if (sp->tmp <= 0)
		{
			sp->tmp = -1;
			*c = '0';
		}
	}
}

void	attack(t_game *game, t_map *map)
{
	char		*c;
	t_sprite	*sp;

	if (game->ammo > 0)
	{
		attack_gun(map);
		return ;
	}
	c = &map->map[(int)(map->pos.y + map->dir.y)][(int)(map->pos.x +
map->dir.x)];
	if (*c == '9')
	{
		if (!(sp = search_sprite(map, (int)(map->pos.x + map->dir.x),
(int)(map->pos.y + map->dir.y))))
			return ;
		if (sp->tmp > 0)
			sp->tmp--;
		if (sp->tmp <= 0)
		{
			*c = '0';
			sp->tmp = -1;
		}
	}
}
