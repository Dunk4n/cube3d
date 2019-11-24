/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:31:48 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 17:36:34 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

static void	key_released_next(int key, t_game *game)
{
	if (key == K_SHIFT)
		game->map->key[P_SHIFT] = 0;
	if (key == K_SPACE)
		secret_porte(game, game->map);
	if (key == K_1)
	{
		game->map = &game->maps[0];
		game->actuel = 0;
	}
	if (key == K_2 && game->ac > 1)
	{
		game->map = &game->maps[1];
		game->actuel = 1;
	}
	if (key == K_3 && game->ac > 2)
	{
		game->map = &game->maps[2];
		game->actuel = 2;
	}
}

int			key_released(int key, t_game *game)
{
	if (key == K_ESC)
		quit_game(game);
	if (key == K_W)
		game->map->key[P_W] = 0;
	if (key == K_S)
		game->map->key[P_S] = 0;
	if (key == K_D)
		game->map->key[P_D] = 0;
	if (key == K_A)
		game->map->key[P_A] = 0;
	if (key == K_E)
		game->map->key[P_E] = 0;
	if (key == K_Q)
		game->map->key[P_Q] = 0;
	if (key == K_RIGHT)
		game->map->key[P_RIGHT] = 0;
	else if (key == K_LEFT)
		game->map->key[P_LEFT] = 0;
	key_released_next(key, game);
	return (0);
}

static void	key_press_next(int key, t_game *game)
{
	if (key == K_SHIFT)
		game->map->key[P_SHIFT] = 1;
	if (key == K_O)
		game->map->h -= 10;
	if (key == K_L)
		game->map->h += 10;
	if (key == K_UP && game->anim_weapon == -1)
	{
		if (game->ammo > 0)
			game->ammo -= 1;
		game->anim_weapon = 0;
		attack(game, game->map);
	}
}

int			key_press(int key, t_game *game)
{
	if (key == K_W)
		game->map->key[P_W] = 1;
	if (key == K_S)
		game->map->key[P_S] = 1;
	if (key == K_D)
		game->map->key[P_D] = 1;
	if (key == K_A)
		game->map->key[P_A] = 1;
	if (key == K_E)
		game->map->key[P_E] = 1;
	if (key == K_Q)
		game->map->key[P_Q] = 1;
	if (key == K_RIGHT)
		game->map->key[P_RIGHT] = 1;
	else if (key == K_LEFT)
		game->map->key[P_LEFT] = 1;
	key_press_next(key, game);
	return (0);
}
