/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:51:55 by niduches          #+#    #+#             */
/*   Updated: 2019/11/19 14:50:10 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*pass_empty_line(int fd, char **line)
{
	int	i;
	int	ret;

	ret = 1;
	while (ret > 0)
	{
		i = 0;
		while ((*line)[i] && ft_isspace((*line)[i]))
			i++;
		if ((*line)[i] && (*line)[i] != '1')
			ret = 0;
		if ((*line)[i])
			break ;
		free(*line);
		if ((ret = get_next_line(fd, line)) == -1)
			return (NULL);
	}
	if (ret == 0)
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	return (*line);
}

static int	empty_line(char *line, int ret)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if ((ret && !line[i]) || (line[i] && line[i] != '1'))
	{
		free(line);
		return (0);
	}
	return (1);
}

static void	set_map_to_null(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->nb_line)
		map->map[i++] = NULL;
}

static int	get_all_map(int fd, t_map *map, int nb)
{
	char	*line;
	int		ret;

	if ((ret = get_next_line(fd, &line)) == -1 || !empty_line(line, ret))
		return (0);
	if (ret == 0 && !*line)
	{
		if (!(map->map = malloc((nb) * sizeof(char*))) ||
!(map->line_size = malloc(nb * sizeof(int))))
		{
			free(line);
			return (0);
		}
		map->nb_line = nb;
		set_map_to_null(map);
		free(line);
		return (1);
	}
	if (!get_all_map(fd, map, nb + 1) ||
!(map->map[nb] = to_good_map(line, map, nb)))
	{
		free(line);
		return (0);
	}
	return (1);
}

int			get_map(int fd, char **line, t_map *map)
{
	if (!(*line = pass_empty_line(fd, line)))
		return (0);
	if (!get_all_map(fd, map, 1))
		return (0);
	if (!(map->map[0] = to_good_map(*line, map, 0)))
		return (0);
	*line = NULL;
	if (!good_map(map))
		return (0);
	return (1);
}
