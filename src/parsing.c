/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:52:06 by niduches          #+#    #+#             */
/*   Updated: 2019/11/15 12:37:20 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cube3d.h"

int		arg_full(t_map *map)
{
	return (map->res.x != -1 && map->tex[NO].tex && map->tex[SO].tex &&
map->tex[WE].tex && map->tex[EA].tex && map->tex[S].tex &&
map->floor.ARGB[A] == 0 && map->roof.ARGB[A] == 0);
}

void	free_identifier(t_map *map, char *line, int fd, void *mlx_ptr)
{
	int	i;

	free(line);
	close(fd);
	mlx_destroy_image(mlx_ptr, map->tex[NO].tex);
	mlx_destroy_image(mlx_ptr, map->tex[SO].tex);
	mlx_destroy_image(mlx_ptr, map->tex[WE].tex);
	mlx_destroy_image(mlx_ptr, map->tex[EA].tex);
	mlx_destroy_image(mlx_ptr, map->tex[S].tex);
	if (!map->map)
		return ;
	i = 0;
	while (i < map->nb_line)
		free(map->map[i++]);
	free(map->map);
	free(map->line_size);
}

int		(*const g_arg_fonction[NB_IDENTIFIER])(int, t_map*, char*,
		void *mlx_ptr) = {
	get_arg_tex, get_arg_tex, get_arg_tex, get_arg_tex, get_arg_tex, get_arg_r,
	get_arg_color, get_arg_color};

int		parse_identifier_line(char *line, t_map *map, void *mlx_ptr)
{
	const char	arg[][3] = {"NO", "SO", "EA", "WE", "S", "R", "F", "C"};
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
		if (!ft_strncmp(line, arg[j - 1], (ft_strlen(arg[j - 1]) < (size_t)i) ?
(size_t)i : ft_strlen(arg[j - 1])))
			return (g_arg_fonction[j - 1](j - 1, map, line + i, mlx_ptr));
	return (0);
}

int		get_file(char *file_name, t_map *map, void *mlx_ptr)
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
		if (!parse_identifier_line(line, map, mlx_ptr))
		{
			ret = -1;
			break ;
		}
		free(line);
	}
	if (ret <= 0 || !get_map(fd, &line, map))
	{
		free_identifier(map, line, fd, mlx_ptr);
		return (0);
	}
	close(fd);
	return (1);
}

int		main(int ac, char **av)
{
	t_map	map;
	void	*mlx_ptr;
	void	*win_ptr;

	if (ac != 2)
		return (0);
	if (!(mlx_ptr = mlx_init()))
		return (0);
	map.res = (t_vec2i){-1, -1};
	map.tex[NO].tex = NULL;
	map.tex[SO].tex = NULL;
	map.tex[WE].tex = NULL;
	map.tex[EA].tex = NULL;
	map.tex[S].tex = NULL;
	map.floor.color = 0;
	map.floor.ARGB[A] = 1;
	map.roof.color = 0;
	map.roof.ARGB[A] = 1;
	map.map = NULL;
	map.line_size = NULL;
	map.nb_line = 0;
	if (!get_file(av[1], &map, mlx_ptr))
	{
		write(1, "ERROR\n", 6);
		return (1);
	}
	return (0);
}
