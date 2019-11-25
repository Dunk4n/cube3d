/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:52:06 by niduches          #+#    #+#             */
/*   Updated: 2019/11/25 11:33:19 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cube3d.h"

static int	arg_full(t_map *map)
{
	return (map->res.x != -1 && map->tex[NO].tex && map->tex[SO].tex &&
map->tex[WE].tex && map->tex[EA].tex && map->tex[S].tex &&
map->floor.argb[A] == 0 && map->roof.argb[A] == 0);
}

int		(*const g_arg_fonction[NB_IDENTIFIER])(int, t_map*, char*,
		void *mlx_ptr) = {
	get_arg_tex, get_arg_tex, get_arg_tex, get_arg_tex, get_arg_tex, get_arg_r,
	get_arg_color, get_arg_color};

const char	g_arg[][3] = {"SO", "WE", "NO", "EA", "S", "R", "F", "C"};

static int	parse_identifier_line(char *line, t_map *map, void *mlx_ptr)
{
	int			i;
	int			j;

	if (!line)
		return (0);
	while (*line && ft_isspace(*line))
		line++;
	if (!(*line))
		return (1);
	i = 0;
	while (*(line + i) && !ft_isspace(*(line + i)))
		i++;
	if (i > 2)
		return (0);
	j = 0;
	while (j++ < NB_IDENTIFIER)
		if (!ft_strncmp(line, g_arg[j - 1], (ft_strlen(g_arg[j - 1]) <
(size_t)i) ? (size_t)i : ft_strlen(g_arg[j - 1])))
			return (g_arg_fonction[j - 1](j - 1, map, line + i, mlx_ptr));
	return (0);
}

static int	good_name(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (i < 4)
		return (0);
	i--;
	if (file_name[i--] != 'b')
		return (0);
	if (file_name[i--] != 'u')
		return (0);
	if (file_name[i--] != 'c')
		return (0);
	if (file_name[i] != '.')
		return (0);
	return (1);
}

int			get_file(char *file_name, t_map *map, void *mlx_ptr)
{
	int		fd;
	char	*line;
	int		ret;

	if (!map || !file_name || !good_name(file_name))
		return (0);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0 && !arg_full(map))
	{
		if (!parse_identifier_line(line, map, mlx_ptr))
		{
			ret = -1;
			break ;
		}
		free(line);
	}
	if (ret <= 0 || !get_map(fd, &line, map))
	{
		free(line);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
