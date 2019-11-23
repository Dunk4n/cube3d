/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:22:43 by niduches          #+#    #+#             */
/*   Updated: 2019/11/23 13:31:43 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d_bonus.h"

void	free_map_sprite(t_map *map, int ac)
{
	free(map->line_size);
	map->line_size = NULL;
	free(map->zbuffer);
	map->zbuffer = NULL;
	free(map->sprite);
	map->sprite = NULL;
	if (ac == 0)
		free(map->dist);
	map->dist = NULL;
}

void	free_map(t_map *map, void *mlx_ptr, int ac)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (mlx_ptr && i <= C)
	{
		if (map->tex[i].tex)
			mlx_destroy_image(mlx_ptr, map->tex[i].tex);
		map->tex[i++].tex = NULL;
	}
	while (mlx_ptr && i < NB_GAME_TEX)
	{
		if (map->tex_game[i].tex && ac == 0)
			mlx_destroy_image(mlx_ptr, map->tex_game[i].tex);
		map->tex_game[i++].tex = NULL;
	}
	if (!map->map)
		return ;
	i = 0;
	while (i < map->nb_line)
		free(map->map[i++]);
	free(map->map);
	map->map = NULL;
	free_map_sprite(map, ac);
}

void	free_all(t_game *game)
{
	free_map(&game->maps[0], game->mlx_ptr, 0);
	if (game->ac > 1)
		free_map(&game->maps[1], game->mlx_ptr, 1);
	if (game->ac > 2)
		free_map(&game->maps[2], game->mlx_ptr, 2);
	if (game->img.tex)
		mlx_destroy_image(game->mlx_ptr, game->img.tex);
}
