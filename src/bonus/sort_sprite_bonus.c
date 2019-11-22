/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:28:38 by niduches          #+#    #+#             */
/*   Updated: 2019/11/22 19:37:05 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int		check_sorted(t_sprite *sprite, int amount, int gap)
{
	int			i;
	int			j;
	t_sprite	tmp;
	char		swapped;

	swapped = 0;
	i = 0;
	while (i < amount - gap)
	{
		j = i + gap;
		if (sprite[i].dist < sprite[j].dist)
		{
			tmp = sprite[i];
			sprite[i] = sprite[j];
			sprite[j] = tmp;
			swapped = 1;
		}
		i++;
	}
	return (swapped);
}

void	sort_sprite(t_map *map)
{
	int			gap;
	char		swapped;
	int			i;

	i = 0;
	while (i < map->nb_sprite)
	{
		map->sprite[i].dist = ((map->pos.x - map->sprite[i].pos.x) *
(map->pos.x - map->sprite[i].pos.x)) + ((map->pos.y - map->sprite[i].pos.y) *
(map->pos.y - map->sprite[i].pos.y));
		i++;
	}
	gap = map->nb_sprite;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swapped = check_sorted(map->sprite, map->nb_sprite, gap);
	}
}
