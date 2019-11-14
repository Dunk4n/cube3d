/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:52:06 by niduches          #+#    #+#             */
/*   Updated: 2019/11/14 17:00:04 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cube3d.h"

int		arg_full(t_map *map)
{
	return (map->res.x != -1 && map->tex[NO] && map->tex[SO] && map->tex[WE] &&
map->tex[EA] && map->tex[S] && map->floor.ARGB[A] == 0 &&
map->roof.ARGB[A] == 0);
}

void	free_identifier(t_map *map, char *line, int fd)
{
	int	i;

	free(line);
	close(fd);
	//TODO: free north ... sprite
	printf("a %p\n", map->map);
	if (!map->map)
		return ;
	i = 0;
	while (map->map[i])
		free(map->map[i++]);
	free(map->map);
	free(map->line_size);
}

int		(*const g_arg_fonction[NB_IDENTIFIER])(int, t_map*, char*) = {
	get_arg_tex, get_arg_tex, get_arg_tex, get_arg_tex, get_arg_tex, get_arg_r,
	get_arg_color, get_arg_color};

int		parse_identifier_line(char *line, t_map *map)
{
	const char	arg[][3] = {"NO", "SO", "WE", "EA", "S", "R", "F", "C"};
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
		if (!ft_strncmp(line, arg[j - 1], (ft_strlen(arg[j - 1]) < i) ? i :
ft_strlen(arg[j - 1])))
			return (g_arg_fonction[j - 1](j - 1, map, line + i));
	return (0);
}

int		get_file(char *file_name, t_map *map)
{
	int		fd;
	char	*line;
	int		ret;

	if (!map || !file_name)
		return (0);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0 && !arg_full(map))
	{
		if (!parse_identifier_line(line, map))
		{
			ret = -1;
			break ;
		}
		free(line);
	}
	if (ret <= 0 || !get_map(fd, &line, map))
	{
		printf("BBB\n");
		free_identifier(map, line, fd);
		printf("BBB\n");
		return (0);
	}
	close(fd);
	return (1);
}

int		main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return (0);
	map.res = (t_vec2i){-1, -1};
	map.tex[NO] = NULL;
	map.tex[SO] = NULL;
	map.tex[WE] = NULL;
	map.tex[EA] = NULL;
	map.tex[S] = NULL;
	map.floor.color = 0;
	map.floor.ARGB[A] = 1;
	map.roof.color = 0;
	map.roof.ARGB[A] = 1;
	map.map = NULL;
	map.line_size = NULL;
	if (!get_file(av[1], &map))
	{
		printf("ERROR MAP\n");
		return (1);
	}
	printf("map = {%d, %d}, floor = %d,%d,%d roof = %d,%d,%d\n",
map.res.x, map.res.y, map.floor.ARGB[R], map.floor.ARGB[G], map.floor.ARGB[B],
map.roof.ARGB[R], map.roof.ARGB[G], map.roof.ARGB[B]);
	return (0);
}
