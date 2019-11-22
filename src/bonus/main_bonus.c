/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:28:28 by niduches          #+#    #+#             */
/*   Updated: 2019/11/22 21:56:29 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d_bonus.h"

int		quit_game(t_game *game)
{
	free_all(game);
	exit(0);
	return (0);
}

t_sprite	*search_sprite(t_map *map, int x, int y)
{
	int			i;
	t_sprite	*sp;

	i = 0;
	while (i < map->nb_sprite)
	{
		sp = &map->sprite[i];
		if ((int)sp->pos.x == x && (int)sp->pos.y == y)
			return (sp);
		i++;
	}
	return (NULL);
}

void	secret_porte(t_map *map)
{
	char		*c;
	t_sprite	*sp;
	int			tmp;

	c = &map->map[(int)(map->pos.y + map->dir.y * map->speed)][(int)(map->pos.x
+ map->dir.x * map->speed)];
	if (*c == '6')
		*c = '0';
	if (*c == '7')
	{
		*c = '0';
		if (!(sp = search_sprite(map, (int)(map->pos.x + map->dir.x * map->speed),
(int)(map->pos.y + map->dir.y * map->speed))))
			return ;
		sp->time = 200;
		tmp = sp->tmp;
		sp->tmp = sp->tex;
		sp->tex = tmp;
	}
}

int		key_released(int key, t_game *game)
{
	if (key == K_ESC)
		quit_game(game);
	if (key == K_W)
		game->map.key[P_W] = 0;
	if (key == K_S)
		game->map.key[P_S] = 0;
	if (key == K_D)
		game->map.key[P_D] = 0;
	if (key == K_A)
		game->map.key[P_A] = 0;
	if (key == K_E)
		game->map.key[P_E] = 0;
	if (key == K_Q)
		game->map.key[P_Q] = 0;
	if (key == K_RIGHT)
		game->map.key[P_RIGHT] = 0;
	else if (key == K_LEFT)
		game->map.key[P_LEFT] = 0;
	if (key == K_SPACE)
		secret_porte(&game->map);
	return (0);
}

int		key_press(int key, t_game *game)
{
	if (key == K_W)
		game->map.key[P_W] = 1;
	if (key == K_S)
		game->map.key[P_S] = 1;
	if (key == K_D)
		game->map.key[P_D] = 1;
	if (key == K_A)
		game->map.key[P_A] = 1;
	if (key == K_E)
		game->map.key[P_E] = 1;
	if (key == K_Q)
		game->map.key[P_Q] = 1;
	if (key == K_RIGHT)
		game->map.key[P_RIGHT] = 1;
	else if (key == K_LEFT)
		game->map.key[P_LEFT] = 1;
	if (key == K_O)
		game->map.h -= 10;
	if (key == K_L)
		game->map.h += 10;
	if (key == K_UP && game->anim_weapon == -1)
	{
		if (game->ammo > 0)
			game->ammo -= 1;
		game->anim_weapon = 0;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 && (ac != 3 || ft_strcmp(av[2], "-save")))
		return (0);
	if (!init_game(&game, av[1]))
	{
		write(1, "ERROR\n", 6);
		free_all(&game);
		return (0);
	}
	if (ac == 3 && !ft_strcmp(av[2], "-save"))
	{
		raycasting(&game.map, &game.img);
		put_in_bmp(&game.img);
		return (0);
	}
	mlx_hook(game.win_ptr, 17, 0L, quit_game, (void*)(&game));
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press, (void*)(&game));
	mlx_hook(game.win_ptr, 3, 1L << 1, key_released, (void*)(&game));
	mlx_loop_hook(game.mlx_ptr, display, (void*)(&game));
	mlx_loop(game.mlx_ptr);
	return (0);
}
