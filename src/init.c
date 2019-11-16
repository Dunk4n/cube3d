/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:50:40 by niduches          #+#    #+#             */
/*   Updated: 2019/11/16 18:49:47 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d.h"

void	init_map(t_map *map)
{
	map->res = (t_vec2i){-1, -1};
	map->tex[NO].tex = NULL;
	map->tex[SO].tex = NULL;
	map->tex[WE].tex = NULL;
	map->tex[EA].tex = NULL;
	map->tex[S].tex = NULL;
	map->floor.color = 0;
	map->floor.ARGB[A] = 1;
	map->roof.color = 0;
	map->roof.ARGB[A] = 1;
	map->map = NULL;
	map->line_size = NULL;
	map->nb_line = 0;
	map->plane.x = 0;
	map->plane.y = 0.66;
}

int	init_game(t_game *game, char *map_name)
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
game->map.res.y)))
		return (0);
	game->img.data = mlx_get_data_addr(game->img.tex, &game->img.bits_per_pixel,
&game->img.size_line, &game->img.endian);
	game->img.size_line /= 4;
	return (1);
}
