/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:36:05 by niduches          #+#    #+#             */
/*   Updated: 2019/11/25 11:36:29 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

static int	good_map_char(char c)
{
	int	i;

	i = 0;
	while (CHAR_MAP[i])
	{
		if (CHAR_MAP[i++] == c)
			return (i);
	}
	return (0);
}

static int	no_border(t_map *map, int y, int x)
{
	if (y == 0 || y == map->nb_line - 1 || x == 0 || x == map->line_size[y] - 1)
		return (1);
	if (x >= map->line_size[y - 1] || x >= map->line_size[y + 1])
		return (1);
	return (0);
}

const t_vec2f	g_dir[4] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
const t_vec2f	g_plane[4] = {{-0.66, 0}, {0, -0.66}, {0.66, 0}, {0, 0.66}};

static int	set_pos(t_map *map, int ret, int x, int y)
{
	if (ret < 4)
	{
		if (map->dir.x != -2)
			return (0);
		map->dir = g_dir[ret];
		map->plane = g_plane[ret];
		map->pos.x = (double)x + 0.5;
		map->pos.y = (double)y + 0.5;
		map->map[(int)y][(int)x] = '0';
	}
	return (1);
}

int			good_map(t_map *map)
{
	int	i;
	int	j;
	int	ret;

	map->dir.x = -2;
	i = 0;
	while (i < map->nb_line)
	{
		j = 0;
		while (j < map->line_size[i])
		{
			if (!(ret = good_map_char(map->map[i][j])))
				return (0);
			if (!set_pos(map, ret - 1, j, i))
				return (0);
			if (map->map[i][j] != '1' && no_border(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return ((map->dir.x == -2) ? 0 : 1);
}
