/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:51:55 by niduches          #+#    #+#             */
/*   Updated: 2019/11/14 17:04:23 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*pass_empty_line(int fd, char **line)
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

int		empty_line(char *line, int ret)
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

int		get_all_map(int fd, t_map *map, int nb)
{
	char	*line;
	int		ret;

	if ((ret = get_next_line(fd, &line)) == -1 || !empty_line(line, ret))
		return (0);
	if (ret == 0 && !*line)
	{
		if (!(map->map = malloc((nb + 1) * sizeof(char*))) ||
!(map->line_size = malloc(nb * sizeof(int))))
		{
			free(line);
			return (0);
		}
		map->nb_line = nb;
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

int		get_map(int fd, char **line, t_map *map)
{
	if (!(*line = pass_empty_line(fd, line)))
		return (0);
	if (!get_all_map(fd, map, 1))
		return (0);
	if (!(map->map[0] = to_good_map(*line, map, 0)))
		return (0);
	*line = NULL;
	//TODO check if map is good
	if (!good_map(map))
	{
		printf("map\n");
		return (0);
	}

	int i = 0;
	if (!map->map)
		return (0);
	while (map->map[i])
	{
		printf("[%s]%d\n", map->map[i], map->line_size[i]);
		i++;
	}
	return (1);
}
