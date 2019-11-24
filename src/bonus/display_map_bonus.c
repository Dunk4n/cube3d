/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:38:09 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 17:22:04 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

static int	chose_color(t_map *map, int i, int j)
{
	int	color;

	color = 0x0000FF00;
	if (map->map[i][j] == '1' || map->map[i][j] == '6')
		color = 0x00FFFFFF;
	else if (map->map[i][j] == '9' || map->map[i][j] == '4')
		color = 0x00FF0000;
	else if (map->map[i][j] == '0')
		color = 0;
	return (color);
}

void		display_map(t_map *map, t_tex *img)
{
	int		i;
	int		j;
	int		size;
	int		pos;

	i = 0;
	pos = map->res.x / 1.65;
	size = map->res.x / 150;
	while (i < map->nb_line && i < 100 && (i + 1) * size < map->res.y)
	{
		j = 0;
		while (j < map->line_size[i] && pos + (j + 1) * size < map->res.x)
		{
			draw_square(img, (t_vec2i){pos + j * size, i * size},
(t_vec2i){size, size}, chose_color(map, i, j));
			j++;
		}
		i++;
	}
	draw_square(img, (t_vec2i){pos + (int)map->pos.x * size, (int)map->pos.y *
size}, (t_vec2i){size, size}, 0x00FFFF00);
}
