/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:30:06 by niduches          #+#    #+#             */
/*   Updated: 2019/11/25 14:30:15 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "cube3d_bonus.h"

int		play_music(char **env, char *sound, char *volum)
{
	pid_t	pid;
	char	*argv[5];

	pid = fork();
	argv[0] = "/usr/bin/afplay";
	argv[1] = "-v";
	argv[2] = volum;
	argv[3] = sound;
	argv[4] = NULL;
	if (pid == 0)
	{
		execve(argv[0], argv, env);
		exit(0);
	}
	return (pid);
}

void	get_coup(t_game *game, int degat)
{
	game->vie -= degat;
	if (game->vie < 0)
		game->vie = 0;
	if (game->coup == 0)
	{
		play_music(game->env, "sound/coup.mp3", "0.6");
		game->coup = 40;
	}
}
