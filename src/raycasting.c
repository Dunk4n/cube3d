/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:07:47 by niduches          #+#    #+#             */
/*   Updated: 2019/11/19 12:29:43 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycasting(t_map *map, t_tex *img)
{
	int		x;
	t_vec3i draw;
	t_vec3i tex;

	x = 0;
	draw_square(img, (t_vec2i){0, 0}, (t_vec2i){map->res.x, map->res.y / 2},
map->roof.color);
	draw_square(img, (t_vec2i){0, map->res.y / 2},
(t_vec2i){map->res.x, map->res.y / 2}, map->floor.color);
	while (x < map->res.x)
	{
		get_wall(map, x, &draw, &tex);
		draw.z = x;
		draw_vline_tex(map, img, draw, tex);
		x++;
	}
	sort_sprite(map);
	display_sprite(map, img);
}
