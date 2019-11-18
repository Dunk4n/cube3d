/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:28:28 by niduches          #+#    #+#             */
/*   Updated: 2019/11/18 18:59:18 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include "cube3d.h"

int		mouse_hook(void *game)
{
	printf("MOUSE\n");
	return (0);
}

int		key_hook(void *game)
{
	printf("KEY\n");
	return (0);
}

int		expose_hook(void *game)
{
	printf("EXPOSE\n");
	return (0);
}

int		quit_game(t_game *game)
{
	printf("QUIT\n");
	free_all(game);
	exit(0);
	return (0);
}

int		key_released(int key, t_game *game)
{
	if (key == K_ESC)
		quit_game(game);
	return (0);
}

int		key_press(int key, t_game *game)
{
	double rot = 0.07;
	double speed = 0.2;

	if (key == K_W || key == K_UP)
	{
		if (game->map.map[(int)game->map.pos.y][(int)(game->map.pos.x + game->map.dir.x * speed)] != '1')
			game->map.pos.x += game->map.dir.x * speed;
		if (game->map.map[(int)(game->map.pos.y + game->map.dir.y * speed)][(int)game->map.pos.x] != '1')
			game->map.pos.y += game->map.dir.y * speed;
	}
	if (key == K_S || key == K_DOWN)
	{
		if (game->map.map[(int)game->map.pos.y][(int)(game->map.pos.x - game->map.dir.x * speed)] != '1')
			game->map.pos.x -= game->map.dir.x * speed;
		if (game->map.map[(int)(game->map.pos.y - game->map.dir.y * speed)][(int)game->map.pos.x] != '1')
			game->map.pos.y -= game->map.dir.y * speed;
	}
	if (key == K_D)
	{
		if (game->map.map[(int)game->map.pos.y][(int)(game->map.pos.x + game->map.plane.x * speed)] != '1')
			game->map.pos.x += game->map.plane.x * speed;
		if (game->map.map[(int)(game->map.pos.y + game->map.plane.y * speed)][(int)game->map.pos.x] != '1')
			game->map.pos.y += game->map.plane.y * speed;
	}
	if (key == K_A)
	{
		if (game->map.map[(int)game->map.pos.y][(int)(game->map.pos.x - game->map.plane.x * speed)] != '1')
			game->map.pos.x -= game->map.plane.x * speed;
		if (game->map.map[(int)(game->map.pos.y - game->map.plane.y * speed)][(int)game->map.pos.x] != '1')
			game->map.pos.y -= game->map.plane.y * speed;
	}
	if (key == K_E || key == K_RIGHT)
	{
		double old_dir_x = game->map.dir.x;
		game->map.dir.x = game->map.dir.x * cos(-rot) - game->map.dir.y * sin(-rot);
		game->map.dir.y = old_dir_x * sin(-rot) + game->map.dir.y * cos(-rot);

		double old_plane_x = game->map.plane.x;
		game->map.plane.x = game->map.plane.x * cos(-rot) - game->map.plane.y * sin(-rot);
		game->map.plane.y = old_plane_x * sin(-rot) + game->map.plane.y * cos(-rot);
		//printf("RIGHT %f, %f\n", game->map.dir.x, game->map.dir.y);
		//printf("RIGHT %f, %f\n\n", game->map.plane.x, game->map.plane.y);
	}
	else if (key == K_Q || key == K_LEFT)
	{
		double old_dir_x = game->map.dir.x;
		game->map.dir.x = game->map.dir.x * cos(rot) - game->map.dir.y * sin(rot);
		game->map.dir.y = old_dir_x * sin(rot) + game->map.dir.y * cos(rot);

		double old_plane_x = game->map.plane.x;
		game->map.plane.x = game->map.plane.x * cos(rot) - game->map.plane.y * sin(rot);
		game->map.plane.y = old_plane_x * sin(rot) + game->map.plane.y * cos(rot);
		//printf("LEFT %f, %f\n", game->map.dir.x, game->map.dir.y);
		//printf("LEFT %f, %f\n\n", game->map.plane.x, game->map.plane.y);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (0);
	if (!init_game(&game, av[1]))
	{
		free_all(&game);
		write(1, "ERROR\n", 6);
		return (1);
	}

//	mlx_do_key_autorepeatoff(game.mlx_ptr);
//	mlx_do_key_autorepeaton(game.mlx_ptr);

	mlx_hook(game.win_ptr, 17, 0L, quit_game, (void*)(&game));
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press, (void*)(&game));
	mlx_hook(game.win_ptr, 3, 1L << 1, key_released, (void*)(&game));
//	mlx_mouse_hook(game.win_ptr, mouse_hook, (void*)(&game));
//	mlx_key_hook(game.win_ptr, key_hook, (void*)(&game));
//	mlx_expose_hook(game.win_ptr, expose_hook, (void*)(&game));
	mlx_loop_hook(game.mlx_ptr, display, (void*)(&game));
	mlx_loop(game.mlx_ptr);
	return (0);
}
