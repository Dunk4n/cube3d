#ifndef CUBE3D_H
# define CUBE3D_H

# include "../lib/libft/libft.h"

# define CHAR_MAP "NSEW012"

enum	union_identifier
{
	NO, SO, EA, WE, S, RE, F, C, NB_IDENTIFIER
};

enum	union_ARGB
{
	B, G, R, A
};

typedef union	u_color
{
	unsigned char	ARGB[4];
	unsigned int	color;
}				t_color;

typedef struct	s_vec2i
{
	int	x;
	int	y;
}				t_vec2i;

typedef	struct	s_map
{
	t_vec2i	res;

	void	*tex[5];

	t_color	floor;
	t_color	roof;

	char	**map;
	int		*line_size;
	int		nb_line;
	char	perso_dir;
}				t_map;

int		get_arg_r(int indice, t_map *map, char *line);
int		get_arg_tex(int indice, t_map *map, char *line);
int		get_arg_color(int indice, t_map *map, char *line);
int		get_map(int fd, char **line, t_map *map);
char	*to_good_map(char *line, t_map *map, int nb);
int		good_map(t_map *map);

#endif
