/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:50:03 by niduches          #+#    #+#             */
/*   Updated: 2019/11/20 13:41:22 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	get_len_of_good_line(char *line)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[i + len])
	{
		while (line[i + len] && ft_isspace(line[i + len]))
			i++;
		while (line[i + len] && !ft_isspace(line[i + len]))
			len++;
	}
	return (len);
}

char		*to_good_map(char *line, t_map *map, int nb)
{
	int		i;
	int		len;
	char	*new_line;

	len = get_len_of_good_line(line);
	if (!(new_line = malloc((len) * sizeof(char))))
		return (NULL);
	map->line_size[nb] = len;
	i = 0;
	len = 0;
	while (len < map->line_size[nb])
	{
		while (line[i + len] && ft_isspace(line[i + len]))
			i++;
		while (line[i + len] && !ft_isspace(line[i + len]))
		{
			new_line[len] = line[i + len];
			len++;
		}
	}
	free(line);
	return (new_line);
}
