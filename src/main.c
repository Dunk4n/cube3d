/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:28:28 by niduches          #+#    #+#             */
/*   Updated: 2021/06/13 16:18:26 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cube3d.h"

int		quit_game(t_game *game)
{
	free_all(game);
	exit(0);
	return (0);
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
	if (key == K_RIGHT)
		game->map.key[P_RIGHT] = 0;
	else if (key == K_LEFT)
		game->map.key[P_LEFT] = 0;
	if (key == K_SPACE)
		game->map.key[P_RIGHT] = 0;
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
	if (key == K_RIGHT)
		game->map.key[P_RIGHT] = 1;
	else if (key == K_LEFT)
		game->map.key[P_LEFT] = 1;
	return (0);
}

int		main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 && (ac != 3 || ft_strcmp(av[2], "-save")))
	{
		ft_printf("./cube3D map_filename.cub [-save]\n-save: save first image to deepthought.bmp\n");
		return (1);
	}
	if (!init_game(&game, av[1]))
	{
		write(1, "ERROR\nparsing\n", 14);
		free_all(&game);
		return (1);
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
