
#include "cube3d.h"

static int	good_map_char(char c)
{
	int	i;

	i = 0;
	while (CHAR_MAP[i])
	{
		if (CHAR_MAP[i++] == c)
			return (i);
	}
	return (0);
}

static int	no_border(t_map *map, int y, int x)
{
	if (y == 0 || y == map->nb_line - 1 || x == 0 || x == map->line_size[y] - 1)
		return (1);
	if (x >= map->line_size[y - 1] || x >= map->line_size[y + 1])
		return (1);
	return (0);
}

static int	set_pos(t_map *map, int	ret, int x, int y)
{
	if (ret <= WE)
	{
		if (map->perso_dir != -1)
			return (0);
		map->perso_dir = ret;
		map->pos.x = x;
		map->pos.y = y;
		map->map[x][y] = '0';
	}
	return (1);
}

int			good_map(t_map *map)
{
	int	i;
	int	j;
	int	ret;

	map->perso_dir = -1;
	i = 0;
	while (i < map->nb_line)
	{
		j = 0;
		while (j < map->line_size[i])
		{
			if (!(ret = good_map_char(map->map[i][j])))
				return (0);
			if (!set_pos(map, ret, j, i))
				return (0);
			if (map->map[i][j] != '1' && no_border(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return ((map->perso_dir == -1) ? 0 : 1);
}
