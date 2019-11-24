/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 13:11:01 by niduches          #+#    #+#             */
/*   Updated: 2019/11/24 19:11:30 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "cube3d_bonus.h"

int			quit_game(t_game *game)
{
	free_all(game);
	if (game->pid > 0)
		kill(game->pid, 3);
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
		if (sp->tmp >= 0 && (int)sp->pos.x == x && (int)sp->pos.y == y)
			return (sp);
		i++;
	}
	return (NULL);
}

void		secret_porte(t_game *game, t_map *map)
{
	char		*c;
	t_sprite	*sp;
	int			tmp;

	c = &map->map[(int)(map->pos.y + map->dir.y * map->speed)][(int)(
map->pos.x + map->dir.x * map->speed)];
	if (*c == '6')
		*c = '0';
	if (*c == '7')
	{
		if (!(sp = search_sprite(map, (int)(map->pos.x + map->dir.x *
map->speed), (int)(map->pos.y + map->dir.y * map->speed))))
			return ;
		if (sp->time == -1 && game->key <= 0)
			return ;
		*c = '0';
		if (sp->time == -1)
			game->key = 0;
		sp->time = 200;
		tmp = sp->tmp;
		sp->tmp = sp->tex;
		sp->tex = tmp;
	}
}

static void	get_img(int ac, char **av)
{
	t_game	game;

	ac--;
	if (!init_game(&game, av + 1, ac))
	{
		write(1, "ERROR\n", 6);
		free_all(&game);
		return ;
	}
	raycasting(game.map, &game.img);
	put_in_bmp(&game.img);
}

int			main(int ac, char **av, char **env)
{
	t_game	game;

	if (ac == 3 && !ft_strcmp(av[2], "-save"))
	{
		get_img(ac, av);
		return (0);
	}
	if (ac < 2 || ac > 4)
		return (0);
	if (!init_game(&game, av + 1, ac))
	{
		write(1, "ERROR\nparsing\n", 14);
		free_all(&game);
		return (0);
	}
	game.env = env;
	game.pid = play_music(env, "sound/resident_evil.mp3", "1");
	mlx_hook(game.win_ptr, 17, 0L, quit_game, (void*)(&game));
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press, (void*)(&game));
	mlx_hook(game.win_ptr, 3, 1L << 1, key_released, (void*)(&game));
	mlx_loop_hook(game.mlx_ptr, display, (void*)(&game));
	mlx_loop(game.mlx_ptr);
	return (0);
}
