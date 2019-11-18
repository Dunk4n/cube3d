/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:22:43 by niduches          #+#    #+#             */
/*   Updated: 2019/11/18 15:02:51 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d.h"

void	free_map_sprite(t_map *map)
{
	free(map->zbuffer);
	map->zbuffer = NULL;
	free(map->sprite);
	map->sprite = NULL;
}

void	free_map(t_map *map, char *line, int fd, void *mlx_ptr)
{
	int	i;

	free(line);
	if (fd > 0)
		close(fd);
	if (!map)
		return ;
	mlx_destroy_image(mlx_ptr, map->tex[NO].tex);
	mlx_destroy_image(mlx_ptr, map->tex[SO].tex);
	mlx_destroy_image(mlx_ptr, map->tex[WE].tex);
	mlx_destroy_image(mlx_ptr, map->tex[EA].tex);
	mlx_destroy_image(mlx_ptr, map->tex[S].tex);
	if (!map->map)
		return ;
	i = 0;
	while (i < map->nb_line)
		free(map->map[i++]);
	free(map->map);
	map->map = NULL;
	free(map->line_size);
	map->line_size = NULL;
	free_map_sprite(map);
}

void	free_all(t_game *game)
{
	free_map(&(game->map), NULL, -1, game->mlx_ptr);
	if (game->img.tex)
		mlx_destroy_image(game->mlx_ptr, game->img.tex);
}
