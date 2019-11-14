/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:52:57 by niduches          #+#    #+#             */
/*   Updated: 2019/11/14 14:57:26 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		get_arg_r(int indice, t_map *map, char *line)
{
	int	i;

	(void)indice;
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
		return (0);
	map->res.x = ft_atoi(line + i);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
		return (0);
	map->res.y = ft_atoi(line + i);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i])
		return (0);
	return (1);
}

int		get_arg_tex(int indice, t_map *map, char *line)
{
	(void)indice;
	(void)map;
	(void)line;
	//TODO
	map->tex[indice] = (void*)1;
	return (1);
}

int		get_arg_color(int indice, t_map *map, char *line)
{
	t_color	*color;

	color = (indice == F) ? &(map->floor) : &(map->roof);
	while (*line && ft_isspace(*line))
		line++;
	color->ARGB[R] = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*(line++) != ',')
		return (0);
	color->ARGB[G] = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*(line++) != ',')
		return (0);
	color->ARGB[B] = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	if (*line)
		return (0);
	color->ARGB[A] = 0;
	return (1);
}
