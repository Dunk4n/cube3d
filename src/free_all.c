/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:22:43 by niduches          #+#    #+#             */
/*   Updated: 2019/11/20 13:23:09 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d.h"

void	free_map_sprite(t_map *map)
{
	free(map->line_size);
	map->line_size = NULL;
	free(map->zbuffer);
	map->zbuffer = NULL;
	free(map->sprite);
	map->sprite = NULL;
}

void	free_map(t_map *map, void *mlx_ptr)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (mlx_ptr && i <= S)
	{
		if (map->tex[i].tex)
			mlx_destroy_image(mlx_ptr, map->tex[i].tex);
		map->tex[i++].tex = NULL;
	}
	if (!map->map)
		return ;
	i = 0;
	while (i < map->nb_line)
		free(map->map[i++]);
	free(map->map);
	map->map = NULL;
	free_map_sprite(map);
}

void	free_all(t_game *game)
{
	free_map(&(game->map), game->mlx_ptr);
	if (game->img.tex)
		mlx_destroy_image(game->mlx_ptr, game->img.tex);
}
