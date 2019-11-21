/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:50:40 by niduches          #+#    #+#             */
/*   Updated: 2019/11/21 17:16:17 by niduches         ###   ########.fr       */
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
	map->rot = 0.04;
	map->speed = 0.1;
	map->dist = NULL;
	i = 0;
	while (i < NB_KEY_PRESSED)
		map->key[i++] = 0;
}

const char	*g_tex_game[NB_GAME_TEX] = {"img/bonus/life.xpm",
"img/bonus/torch1.xpm", "img/bonus/torch2.xpm", "img/bonus/torch3.xpm",
"img/bonus/torch4.xpm"};

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
		i++;
	}
	return (1);
}

int			init_game(t_game *game, char *map_name)
{
	init_map(&(game->map));
	game->win_ptr = NULL;
	game->img.tex = NULL;
	if (!(game->mlx_ptr = mlx_init()))
		return (0);
	if (!get_file(map_name, &game->map, game->mlx_ptr))
		return (0);
	if (!(game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.res.x,
game->map.res.y, "cube3d")))
		return (0);
	game->img.size.x = game->map.res.x;
	game->img.size.y = game->map.res.y;
	if (!(game->img.tex = mlx_new_image(game->mlx_ptr, game->map.res.x,
game->map.res.y)) || !(get_all_tex(&game->map, game->mlx_ptr)))
		return (0);
	game->img.data = mlx_get_data_addr(game->img.tex, &game->img.bits_per_pixel,
&game->img.size_line, &game->img.endian);
	game->img.size_line /= 4;
	if (!get_sprite(&game->map))
		return (0);
	if (!(game->map.dist = malloc(game->map.height_d2 * sizeof(double))))
		return (0);
	game->map.dist[0] = -1;
	return (1);
}
