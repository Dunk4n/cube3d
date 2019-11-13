#include <unistd.h>
#include <fcntl.h>
#include "cube3d.h"

int		arg_full(t_map *map)
{
	return (map->res.x != -1 && map->tex[NO] && map->tex[SO] && map->tex[WE] &&
map->tex[EA] && map->tex[S] && map->floor.ARGB[A] == 0 && map->roof.ARGB[A] == 0
/*&& map->map*/);
}

void	free_identifier(t_map *map)
{
	int	i;

	//TODO: free north ... sprite
	if (!map->map)
		return ;
	i = 0;
	while (map->map[i])
		free(map->map[i++]);
	free(map->map);
	free(map->line_size);
}

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

const int	(*g_arg_fonction[NB_IDENTIFIER])(int, t_map*, char*) = {get_arg_tex, get_arg_tex, get_arg_tex, get_arg_tex, get_arg_tex, get_arg_r,
get_arg_color, get_arg_color};

int		parse_identifier_line(char *line, t_map *map)
{
	const char	arg[][3] = {"NO", "SO", "WE", "EA", "S", "R", "F", "C"};
	int			i;
	int			j;
	int			k;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	j = 0;
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	if (j > 2)
		return (0);
	k = 0;
	while (k++ < NB_IDENTIFIER)
		if (!ft_strncmp(line, arg[k - 1], (ft_strlen(arg[k - 1]) < j) ? j :
ft_strlen(arg[k - 1])))
			return (g_arg_fonction[k - 1](k - 1, map, line + i + j));
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
	//	printf("line = [%s]\nfull? = %d\n\n", line, arg_full(map));
		if (!parse_identifier_line(line, map))
		{
			free(line);
			free_identifier(map);
			close(fd);
			return (0);
		}
		free(line);
	}
	if (ret == 0)
		free(line);
/*	if (!get_map(fd, map))
	{
		close(fd);
		return (0);
	}*/
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
		return (1);
	printf("map = {%d, %d}, floor = %08x roof = %08x\n", map.res.x, map.res.y, map.floor.color, map.roof.color);
	return (0);
}
