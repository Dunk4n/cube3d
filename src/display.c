/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:53:13 by niduches          #+#    #+#             */
/*   Updated: 2019/11/20 14:46:30 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include "cube3d.h"

static void	move_to(t_map *map, t_vec2f dir, double speed)
{
	int	y;
	int	x;

	x = (int)(map->pos.x + dir.x * speed);
	if (x > 0 && x < map->line_size[(int)map->pos.y] && ((int)map->pos.y == 0 ||
x < map->line_size[(int)map->pos.y - 1]) &&
((int)map->pos.y == map->nb_line - 1 || x < map->line_size[(int)map->pos.y + 1])
	&& map->map[(int)map->pos.y][x] != '1')
		map->pos.x += dir.x * speed;
	y = (int)(map->pos.y + dir.y * speed);
	if (y > 0 && y < map->nb_line && map->map[y][(int)map->pos.x] != '1')
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

static void	update_key(t_game *game)
{
	if (game->map.key[P_W])
		move_to(&game->map, game->map.dir, game->map.speed);
	if (game->map.key[P_S])
		move_to(&game->map, game->map.dir, -game->map.speed);
	if (game->map.key[P_D])
		move_to(&game->map, game->map.plane, game->map.speed);
	if (game->map.key[P_A])
		move_to(&game->map, game->map.plane, -game->map.speed);
	if (game->map.key[P_RIGHT])
		rotate_to(&game->map, game->map.rot);
	if (game->map.key[P_LEFT])
		rotate_to(&game->map, -game->map.rot);
}

int			display(t_game *game)
{
	raycasting(&game->map, &game->img);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.tex, 0, 0);
	update_key(game);
	return (0);
}
