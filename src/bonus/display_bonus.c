/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:53:13 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 16:45:58 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include "cube3d_bonus.h"

static void	put_pixel(t_tex *img, int color, int x, int y)
{
	if ((color & 0x00ffffff) != 0)
		((int*)img->data)[x + (y * img->size_line)] = color;
}

static void	put_img(t_tex *img, t_tex *to_print, t_vec2f pos, t_vec2f ratio)
{
	float	x;
	float	y;
	int		i;
	int		j;
	t_vec2i	len;

	len.x = img->size.x / ratio.x;
	x = (double)to_print->size.x / (double)len.x;
	len.y = img->size.y / ratio.y;
	y = (double)to_print->size.y / (double)len.y;
	pos.x = len.x * pos.x;
	pos.y = len.y * pos.y;
	i = 0;
	while (i < len.y)
	{
		j = 0;
		while (j < len.x)
		{
			put_pixel(img, ((int*)to_print->data)[(int)(j * x) + ((int)(i * y) *
to_print->size_line)], j + (int)pos.x, (i + (int)pos.y));
			j++;
		}
		i++;
	}
}

static void	display_hud(t_game *game, t_tex *img)
{
	int	i;

	draw_square(img, (t_vec2i){img->size.x / 14, img->size.y / 9},
(t_vec2i){img->size.x / 4.9 * ((float)game->vie / (float)game->vie_max),
img->size.y / 24}, 0x0000FF00);
	put_img(img, &game->map->tex_game[LIFE], (t_vec2f){0, 0}, (t_vec2f){3, 4});
	if (game->ammo <= 0)
		put_img(img, &game->map->tex_game[game->anim_torch / 5 + TORCH1],
(t_vec2f){1, 1}, (t_vec2f){5, 2});
	put_img(img, &game->map->tex_game[game->anim_weapon / 5 +
((game->ammo > 0) ? GUN1 : KNIFE1)], (t_vec2f){0, 0}, (t_vec2f){1, 1});
	game->anim_torch = (game->anim_torch + 1) % 20;
	if (game->anim_weapon >= 0)
		game->anim_weapon = (game->anim_weapon + 1);
	if (game->anim_weapon == 25)
		game->anim_weapon = -1;
	i = 0;
	while (i < game->ammo - 1)
		put_img(img, &game->map->tex_game[AMMO], (t_vec2f){i++, 0},
(t_vec2f){15, 15});
	if (game->key)
		put_img(img, &game->map->tex_game[KEY_HUD], (t_vec2f){0, 7},
(t_vec2f){8, 8});
}

static void	update_sprite(t_game *game)
{
	int			i;
	int			tmp;
	t_sprite	*sp;

	i = 0;
	while (i < game->map->nb_sprite)
	{
		sp = &game->map->sprite[i++];
		if (sp->tex == MONSTER && sp->tmp > 0)
			if ((game->map->pos.x - sp->pos.x) * (game->map->pos.x - sp->
pos.x) + (game->map->pos.y - sp->pos.y) * (game->map->pos.y - sp->pos.y) <= 1.5)
				game->vie -= 3;
		if (sp->time > 0)
			sp->time--;
		if (sp->tex == TDOOR && sp->time == 0 && ((int)sp->pos.x !=
(int)game->map->pos.x || (int)sp->pos.y != (int)game->map->pos.y))
		{
			tmp = sp->tmp;
			sp->tmp = sp->tex;
			sp->tex = tmp;
			game->map->map[(int)sp->pos.y][(int)sp->pos.x] = '7';
		}
	}
}

int			display(t_game *game)
{
	raycasting(game->map, &game->img);
	display_hud(game, &game->img);
	display_map(game->map, &game->img);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.tex, 0, 0);
	if (game->actuel == 0)
		mlx_string_put(game->mlx_ptr, game->win_ptr, 0, 0, 0x00FF0000, "0");
	else if (game->actuel == 1)
		mlx_string_put(game->mlx_ptr, game->win_ptr, 0, 0, 0x0000FF00, "1");
	else if (game->actuel == 2)
		mlx_string_put(game->mlx_ptr, game->win_ptr, 0, 0, 0x000000FF, "2");
	update_key(game);
	check_if_obj(game, &game->map->map[(int)game->map->pos.y][(int)game->
map->pos.x], (int)game->map->pos.x, (int)game->map->pos.x);
	update_sprite(game);
	if (game->vie <= 0)
		quit_game(game);
	return (0);
}
