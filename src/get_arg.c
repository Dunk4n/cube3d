/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:52:57 by niduches          #+#    #+#             */
/*   Updated: 2019/11/20 14:10:17 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		get_arg_r(int indice, t_map *map, char *line, void *mlx_ptr)
{
	int	i;

	(void)indice;
	(void)mlx_ptr;
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

int		get_arg_tex(int indice, t_map *map, char *line, void *mlx_ptr)
{
	int	i;
	int	j;

	while (ft_isspace(*line))
		line++;
	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	j = 0;
	while (line[i + j] && ft_isspace(line[i + j]))
		j++;
	if (line[i + j])
		return (0);
	line[i] = '\0';
	if (!(map->tex[indice].tex = mlx_xpm_file_to_image(mlx_ptr, line,
&(map->tex[indice].size.x), &(map->tex[indice].size.y))))
		return (0);
	map->tex[indice].data = mlx_get_data_addr(map->tex[indice].tex,
&(map->tex[indice].bits_per_pixel), &(map->tex[indice].size_line),
&(map->tex[indice].endian));
	return (1);
}

int		get_arg_color(int indice, t_map *map, char *line, void *mlx_ptr)
{
	t_color	*color;

	(void)mlx_ptr;
	color = (indice == F) ? &(map->floor) : &(map->roof);
	while (*line && ft_isspace(*line))
		line++;
	color->argb[R] = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*(line++) != ',')
		return (0);
	color->argb[G] = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*(line++) != ',')
		return (0);
	color->argb[B] = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	while (*line && ft_isspace(*line))
		line++;
	if (*line)
		return (0);
	color->argb[A] = 0;
	return (1);
}
