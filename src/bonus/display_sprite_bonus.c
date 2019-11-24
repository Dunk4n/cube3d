/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:28:01 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 15:51:36 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

static void		get_transform(t_map *map, t_sprite_draw *draw, int i)
{
	t_vec2f	sprite_pos;
	double	inv;

	sprite_pos.x = map->sprite[i].pos.x - map->pos.x;
	sprite_pos.y = map->sprite[i].pos.y - map->pos.y;
	inv = 1.0 / (map->plane.x * map->dir.y - map->dir.x * map->plane.y);
	draw->transform.x = inv *
(map->dir.y * sprite_pos.x - map->dir.x * sprite_pos.y);
	draw->transform.y = inv *
(-map->plane.y * sprite_pos.x + map->plane.x * sprite_pos.y);
	draw->sprite_screen_x = (int)((map->res.x / 2) *
(1 + draw->transform.x / draw->transform.y));
	draw->sprite_height = ABS((int)(map->res.y / draw->transform.y));
}

static void		get_draw(t_map *map, t_sprite_draw *draw)
{
	draw->draw_start.y = -draw->sprite_height / 2 + map->height_d2 + map->h;
	if (draw->draw_start.y < 0)
		draw->draw_start.y = 0;
	draw->draw_end.y = draw->sprite_height / 2 + map->height_d2 + map->h;
	if (draw->draw_end.y >= map->res.y)
		draw->draw_end.y = map->res.y;
	draw->draw_start.x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_start.x < 0)
		draw->draw_start.x = 0;
	draw->draw_end.x = draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_end.x >= map->res.x)
		draw->draw_end.x = map->res.x;
}

static void		draw_sprite(t_map *map, t_tex *img, t_sprite_draw *draw,
t_vec2i cnt)
{
	int		y;
	int		d;
	t_color	color;

	y = draw->draw_start.y;
	while (y < draw->draw_end.y)
	{
		d = (y - map->h) * 256 - map->res.y * 128 + draw->sprite_height * 128;
		draw->tex.y = ((d * map->tex_game[map->sprite[cnt.x - 1].tex].size.y) /
draw->sprite_height) / 256;
		color.color = ((int*)map->tex_game[map->sprite[cnt.x - 1].tex].data)[
draw->tex.y * map->tex_game[map->sprite[cnt.x - 1].tex].size.x + draw->tex.x];
		if ((color.color & 0x00ffffff) != 0)
		{
			color.argb[R] *= draw->tmp;
			color.argb[G] *= draw->tmp;
			color.argb[B] *= draw->tmp;
			((int*)img->data)[cnt.y + (y * img->size_line)] = color.color;
		}
		y++;
	}
}

static double	get_fact(t_map *map, t_vec2i cnt, t_sprite_draw *draw)
{
	double			fact;

	fact = (map->sprite[cnt.x - 1].dist / 50) + 0.5;
	if (fact < 0)
		fact = 0;
	if (fact > 1)
		fact = 1;
	fact = 1 - fact;
	get_transform(map, draw, cnt.x - 1);
	return (fact);
}

void			display_sprite(t_map *map, t_tex *img)
{
	t_vec2i			cnt;
	t_sprite_draw	draw;

	cnt.x = 0;
	while (cnt.x++ < map->nb_sprite)
	{
		if (map->sprite[cnt.x - 1].dist > 35 ||
map->sprite[cnt.x - 1].tmp == -1)
			continue ;
		draw.tmp = get_fact(map, cnt, &draw);
		draw.sprite_width = ABS((int)(map->res.y / draw.transform.y));
		get_draw(map, &draw);
		cnt.y = draw.draw_start.x;
		while (cnt.y < draw.draw_end.x)
		{
			draw.tex.x = (int)(256 * (cnt.y - (-draw.sprite_width / 2 +
draw.sprite_screen_x)) * map->tex_game[map->sprite[cnt.x - 1].tex].size.x /
draw.sprite_width) / 256;
			if (draw.transform.y > 0 && cnt.y >= 0 && cnt.y < map->res.x &&
draw.transform.y < map->zbuffer[cnt.y])
				draw_sprite(map, img, &draw, cnt);
			cnt.y++;
		}
	}
}
