/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 20:04:17 by niduches          #+#    #+#             */
/*   Updated: 2019/11/17 17:45:41 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <mlx.h>
# include "../lib/libft/libft.h"
# include "keys.h"

# define CHAR_MAP "NSEW012"
# define ABS(x) (((x) < 0) ? -(x) : (x))

enum	union_identifier
{
	NO, WE, SO, EA, S, RE, F, C, NB_IDENTIFIER
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

typedef struct	s_vec3i
{
	int	x;
	int	y;
	int	z;
}				t_vec3i;

typedef struct	s_vec2f
{
	double	x;
	double	y;
}				t_vec2f;

typedef	struct	s_tex
{
	void	*tex;
	char	*data;
	t_vec2i	size;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_tex;

typedef	struct	s_map
{
	t_vec2i	res;

	t_tex	tex[5];

	t_color	floor;
	t_color	roof;

	char	**map;
	int		*line_size;
	int		nb_line;
	t_vec2f	dir;
	t_vec2f	pos;
	t_vec2f	plane;
}				t_map;

typedef struct	s_game
{
	t_map	map;
	void	*mlx_ptr;
	void	*win_ptr;
	t_tex	img;
}				t_game;

int		get_file(char *file_name, t_map *map, void *mlx_ptr);
int		get_arg_r(int indice, t_map *map, char *line, void *mlx_ptr);
int		get_arg_tex(int indice, t_map *map, char *line, void *mlx_ptr);
int		get_arg_color(int indice, t_map *map, char *line, void *mlx_ptr);
int		get_map(int fd, char **line, t_map *map);
char	*to_good_map(char *line, t_map *map, int nb);
int		good_map(t_map *map);
void	free_map(t_map *map, char *line, int fd, void *mlx_ptr);
void	free_all(t_game *game);
int		init_game(t_game *game, char *map_name);
int		display(t_game *game);
void	raycasting(t_map *map, t_tex *img);
void	draw_vertical_line(t_tex *img, int x, t_vec2i draw, int color);

#endif
