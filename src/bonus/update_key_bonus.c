/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_key_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:42:27 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 17:23:35 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cube3d_bonus.h"

static int	can_walk(char c)
{
	int	i;

	i = 0;
	while (CAN_WALK[i])
		if (CAN_WALK[i++] == c)
			return (1);
	return (0);
}

void		check_if_obj(t_game *game, char *c)
{
	if (*c == '0')
		return ;
	if (*c == '3')
		game->ammo = 6;
	else if (*c == '4')
	{
		game->vie -= 15;
		if (game->vie < 0)
			game->vie = 0;
	}
	else if (*c == '5')
	{
		game->vie += 3;
		if (game->vie > game->vie_max)
			game->vie = game->vie_max;
	}
	else if (*c == '8' && game->key == 0)
	{
		*c = '0';
		game->key = 1;
		search_sprite(game->map, (int)game->map->pos.x,
(int)game->map->pos.y)->tmp = -1;
	}
}

static void	move_to(t_map *map, t_vec2f dir, double speed)
{
	int	y;
	int	x;

	x = (int)(map->pos.x + dir.x * speed);
	if (x > 0 && x < map->line_size[(int)map->pos.y] && ((int)map->pos.y == 0 ||
x < map->line_size[(int)map->pos.y - 1]) &&
((int)map->pos.y == map->nb_line - 1 || x < map->line_size[(int)map->pos.y + 1])
	&& can_walk(map->map[(int)map->pos.y][x]))
		map->pos.x += dir.x * speed;
	y = (int)(map->pos.y + dir.y * speed);
	if (y > 0 && y < map->nb_line && can_walk(map->map[y][(int)map->pos.x]))
		map->pos.y += dir.y * speed;
}

static void	rotate_to(t_map *map, double rot)
{
	double old;

	old = map->dir.x;
	map->dir.x = map->dir.x * cos(rot) - map->dir.y * sin(rot);
	map->dir.y = old * sin(rot) + map->dir.y * cos(rot);
	old = map->plane.x;
	map->plane.x = map->plane.x * cos(rot) - map->plane.y * sin(rot);
	map->plane.y = old * sin(rot) + map->plane.y * cos(rot);
}

void		update_key(t_game *game)
{
	float	fact;

	fact = (game->map->key[P_SHIFT]) ? 2 : 1;
	if (game->map->key[P_W])
		move_to(game->map, game->map->dir, game->map->speed * fact);
	if (game->map->key[P_S])
		move_to(game->map, game->map->dir, -game->map->speed * fact);
	if (game->map->key[P_D])
		move_to(game->map, game->map->plane, game->map->speed * fact);
	if (game->map->key[P_A])
		move_to(game->map, game->map->plane, -game->map->speed * fact);
	if (game->map->key[P_RIGHT] || game->map->key[P_E])
		rotate_to(game->map, game->map->rot);
	if (game->map->key[P_LEFT] || game->map->key[P_Q])
		rotate_to(game->map, -game->map->rot);
}
