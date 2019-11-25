/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:50:40 by niduches          #+#    #+#             */
/*   Updated: 2019/11/25 10:34:18 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d_bonus.h"

static void	init_map(t_map *map)
{
	int	i;

	map->res = (t_vec2i){-1, -1};
	i = 0;
	while (i <= C)
		map->tex[i++].tex = NULL;
	i = 0;
	while (i <= NB_GAME_TEX)
		map->tex_game[i++].tex = NULL;
	map->map = NULL;
	map->line_size = NULL;
	map->nb_line = 0;
	map->zbuffer = NULL;
	map->sprite = NULL;
	map->nb_sprite = 0;
	map->rot = 0.05;
	map->speed = 0.06;
	map->dist = NULL;
	i = 0;
	while (i < NB_KEY_PRESSED)
		map->key[i++] = 0;
	map->h = 0;
}

const char	*g_tex_game[NB_GAME_TEX] = {"img/bonus/life.xpm",
	"img/bonus/torch1.xpm", "img/bonus/torch2.xpm", "img/bonus/torch3.xpm",
	"img/bonus/torch4.xpm", "img/bonus/knife1.xpm", "img/bonus/knife2.xpm",
	"img/bonus/knife3.xpm", "img/bonus/knife4.xpm", "img/bonus/knife5.xpm",
	"img/bonus/gun1.xpm", "img/bonus/gun2.xpm", "img/bonus/gun3.xpm",
	"img/bonus/gun4.xpm", "img/bonus/gun5.xpm", "img/bonus/gun.xpm",
	"img/bonus/skull.xpm", "img/bonus/companion.xpm", "img/bonus/ammo.xpm",
	"img/bonus/door.xpm", "img/bonus/tdoor.xpm", "img/bonus/key.xpm",
	"img/bonus/key_hud.xpm", "img/bonus/scream.xpm"};

static int	get_all_tex(t_map *map, void *mlx_ptr)
{
	int	i;

	i = 0;
	while (i < NB_GAME_TEX)
	{
		if (!(map->tex_game[i].tex = mlx_xpm_file_to_image(mlx_ptr,
(char*)g_tex_game[i], &(map->tex_game[i].size.x), &(map->tex_game[i].size.y))))
			return (0);
		map->tex_game[i].data = mlx_get_data_addr(map->tex_game[i].tex,
&(map->tex_game[i].bits_per_pixel), &(map->tex_game[i].size_line),
&(map->tex_game[i].endian));
		map->tex_game[i].size_int.x = map->tex_game[i].size.x / 4;
		map->tex_game[i].size_int.y = map->tex_game[i].size.y / 4;
		map->tex_game[i].size_line /= 4;
		i++;
	}
	map->tex_game[i] = map->tex[4];
	return (1);
}

static void	init_var_game(t_game *game)
{
	game->anim_torch = 0;
	game->anim_weapon = -1;
	game->ammo = -1;
	game->vie_max = 1000;
	game->vie = game->vie_max;
	game->key = 0;
	init_map(&(game->maps[0]));
	init_map(&(game->maps[1]));
	init_map(&(game->maps[2]));
}

static int	get_all_maps(t_game *game, char **av, int ac)
{
	int	i;
	int	j;

	if (!get_file(av[0], &game->maps[0], game->mlx_ptr))
		return (0);
	if (!(get_all_tex(&game->maps[0], game->mlx_ptr)) || !(game->maps[0].dist =
malloc(game->maps[0].height_d2 * sizeof(double))))
		return (0);
	game->maps[0].dist[0] = -1;
	if (!get_sprite(&game->maps[0]))
		return (0);
	i = 0;
	while (++i < ac)
	{
		if (!get_file(av[i], &game->maps[i], game->mlx_ptr))
			return (0);
		game->maps[i].res = game->maps[0].res;
		game->maps[i].dist = game->maps[0].dist;
		j = 0;
		while (j++ <= NB_GAME_TEX)
			game->maps[i].tex_game[j - 1] = game->maps[0].tex_game[j - 1];
		if (!get_sprite(&game->maps[i]))
			return (0);
	}
	return (1);
}

int			init_game(t_game *game, char **av, int ac)
{
	init_var_game(game);
	game->win_ptr = NULL;
	game->img.tex = NULL;
	if (!(game->mlx_ptr = mlx_init()))
		return (0);
	if (!get_all_maps(game, av, ac - 1))
		return (0);
	game->ac = ac - 1;
	game->actuel = 0;
	game->map = &game->maps[0];
	if (!(game->win_ptr = mlx_new_window(game->mlx_ptr, game->map->res.x,
game->map->res.y, "cube3d")))
		return (0);
	game->img.size.x = game->map->res.x;
	game->img.size.y = game->map->res.y;
	if (!(game->img.tex = mlx_new_image(game->mlx_ptr, game->map->res.x,
game->map->res.y)))
		return (0);
	game->img.data = mlx_get_data_addr(game->img.tex, &game->img.bits_per_pixel,
&game->img.size_line, &game->img.endian);
	game->img.size_line /= 4;
	return (1);
}
