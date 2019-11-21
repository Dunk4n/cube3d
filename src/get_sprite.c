/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:31:02 by niduches          #+#    #+#             */
/*   Updated: 2019/11/21 16:33:40 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cube3d.h"

static int	get_nb_sprite(t_map *map)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	while (i < map->nb_line)
	{
		j = 0;
		while (j < map->line_size[i])
		{
			if (map->map[i][j] == '2')
				nb++;
			j++;
		}
		i++;
	}
	return (nb);
}

static int	set_sprite(t_map *map)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	while (i < map->nb_line)
	{
		j = 0;
		while (j < map->line_size[i])
		{
			if (map->map[i][j] == '2')
			{
				map->sprite[nb].tex = 4;
				map->sprite[nb].dist = 0;
				map->sprite[nb].pos.x = (double)j + 0.5;
				map->sprite[nb].pos.y = (double)i + 0.5;
				nb++;
			}
			j++;
		}
		i++;
	}
	return (nb);
}

int			get_sprite(t_map *map)
{
	int	i;

	if (!(map->zbuffer = malloc(map->res.x * sizeof(double))))
		return (0);
	i = 0;
	while (i < map->res.x)
		map->zbuffer[i++] = 0;
	map->nb_sprite = get_nb_sprite(map);
	if (!(map->sprite = malloc(map->nb_sprite * sizeof(t_sprite))))
		return (0);
	set_sprite(map);
	return (1);
}
