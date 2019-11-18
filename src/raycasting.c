/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:07:47 by niduches          #+#    #+#             */
/*   Updated: 2019/11/18 19:14:30 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cube3d.h"

void	display_sprite(t_map *map, t_tex *img)
{
	int		i;
	t_vec2f	sprite_pos;
	t_vec2f	transform;
	double	inv;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	t_vec2i	draw_start;
	t_vec2i	draw_end;
	int		stripe;
	int		y;
	t_vec2i	tex;
	int		d;
	int		color;

	i = 0;
	while (i < map->nb_sprite)
	{
		sprite_pos.x = map->sprite[i].pos.x - map->pos.x;
		sprite_pos.y = map->sprite[i].pos.y - map->pos.y;
		inv = 1.0 / (map->plane.x * map->dir.y - map->dir.x * map->plane.y);
		transform.x = inv * (map->dir.y * sprite_pos.x - map->dir.x * sprite_pos.y);
		transform.y = inv * (-map->plane.y * sprite_pos.x + map->plane.x * sprite_pos.y);

		sprite_screen_x = (int)((map->res.x / 2) * (1 + transform.x / transform.y));

		sprite_height = ABS((int)(map->res.y / transform.y));
		draw_start.y = -sprite_height / 2 + map->res.y / 2;
		if (draw_start.y < 0)
			draw_start.y = 0;
		draw_end.y = sprite_height / 2 + map->res.y / 2;
		if (draw_end.y >= map->res.y)
			draw_end.y = map->res.y - 1;

		sprite_width = ABS((int)(map->res.y / transform.y));
		draw_start.x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start.x < 0)
			draw_start.x = 0;
		draw_end.x = sprite_width / 2 + sprite_screen_x;
		if (draw_end.x >= map->res.x)
			draw_end.x = map->res.x - 1;

		stripe = draw_start.x;
		while (stripe < draw_end.x)
		{
			tex.x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
* map->tex[map->sprite[i].tex].size.x / sprite_width) / 256;
			if (transform.y > 0 && stripe > 0 && stripe < map->res.x && transform.y < map->zbuffer[stripe])
			{
				y = draw_start.y;
				while (y < draw_end.y)
				{
					d = y * 256 - map->res.y * 128 + sprite_height * 128;
					tex.y = ((d * map->tex[map->sprite[i].tex].size.y) / sprite_height) / 256;
					color = ((int*)map->tex[map->sprite[i].tex].data)[tex.y *
map->tex[map->sprite[i].tex].size.x + tex.x];
					if ((color & 0x00ffffff) != 0)
						((int*)img->data)[stripe + (y * img->size_line)] = color;
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}

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
