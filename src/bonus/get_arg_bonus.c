/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:52:57 by niduches          #+#    #+#             */
/*   Updated: 2019/11/25 14:02:10 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void	check_scree_size(t_map *map)
{
	if (map->res.x > 2880)
		map->res.x = 2880;
	if (map->res.y > 1800)
		map->res.y = 1800;
	map->height_d2 = map->res.y / 2;
}

int		get_arg_r(int indice, t_map *map, char *line, void *mlx_ptr)
{
	int	i;

	(void)indice;
	(void)mlx_ptr;
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]) || map->res.x != -1)
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
	check_scree_size(map);
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
	if (line[i + j] || map->tex[indice].tex)
		return (0);
	line[i] = '\0';
	if (!(map->tex[indice].tex = mlx_xpm_file_to_image(mlx_ptr, line,
&(map->tex[indice].size.x), &(map->tex[indice].size.y))))
		return (0);
	map->tex[indice].data = mlx_get_data_addr(map->tex[indice].tex,
&(map->tex[indice].bits_per_pixel), &(map->tex[indice].size_line),
&(map->tex[indice].endian));
	map->tex[indice].size_int.x = map->tex[indice].size.x / 4;
	map->tex[indice].size_int.y = map->tex[indice].size.y / 4;
	return (1);
}
