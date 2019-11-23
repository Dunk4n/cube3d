/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:53:13 by niduches          #+#    #+#             */
/*   Updated: 2019/11/23 17:40:51 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

static void	check_if_obj(t_game *game, char *c, int x, int y)
{
	t_sprite	*sp;

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
		sp = search_sprite(game->map, (int)game->map->pos.x,
(int)game->map->pos.y);
		sp->tmp = -1;
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

static void	update_key(t_game *game)
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

void		put_pixel(t_tex *img, int color, int x, int y)
{
	if ((color & 0x00ffffff) != 0)
		((int*)img->data)[x + (y * img->size_line)] = color;
}

void		put_img(t_tex *img, t_tex *to_print, t_vec2f pos, t_vec2f ratio)
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

void		display_hud(t_game *game, t_tex *img)
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

void		update_sprite(t_game *game)
{
	int			i;
	int			tmp;
	t_sprite	*sp;

	i = 0;
	while (i < game->map->nb_sprite)
	{
		sp = &game->map->sprite[i];
		if (sp->tex == MONSTER && sp->tmp > 0)
		{
			if ((game->map->pos.x - sp->pos.x) * (game->map->pos.x - sp->pos.x)
+ (game->map->pos.y - sp->pos.y) * (game->map->pos.y - sp->pos.y) <= 1.5)
				game->vie -= 3;
		}
		if (sp->time > 0)
		{
			sp->time--;
		}
		if (sp->tex == TDOOR && sp->time == 0 && ((int)sp->pos.x !=
(int)game->map->pos.x || (int)sp->pos.y != (int)game->map->pos.y))
		{
			tmp = sp->tmp;
			sp->tmp = sp->tex;
			sp->tex = tmp;
			game->map->map[(int)sp->pos.y][(int)sp->pos.x] = '7';
		}
		i++;
	}
}

void		display_map(t_map *map, t_tex *img)
{
	int		i;
	int		j;
	int		size;
	int		pos;
	int		color;

	i = 0;
	pos = map->res.x / 1.65;
	size = map->res.x / 150;
	while (i < map->nb_line && i < 100 && (i + 1) * size < map->res.y)
	{
		j = 0;
		while (j < map->line_size[i] && j < 100 && pos + (j + 1) * size < map->res.x)
		{
			color = 0x0000FF00;
			if (map->map[i][j] == '1' || map->map[i][j] == '6')
				color = 0x00FFFFFF;
			else if (map->map[i][j] == '9' || map->map[i][j] == '4')
				color = 0x00FF0000;
			else if (map->map[i][j] == '0')
				color = 0;
			draw_square(img, (t_vec2i){pos + j * size, i * size},
(t_vec2i){size, size}, color);
			j++;
		}
		i++;
	}
	draw_square(img, (t_vec2i){pos + (int)map->pos.x * size, (int)map->pos.y *
size}, (t_vec2i){size, size}, 0x00FFFF00);
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
