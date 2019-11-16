/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:04:28 by niduches          #+#    #+#             */
/*   Updated: 2019/11/16 19:04:17 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_vertical_line(t_tex *img, int x, t_vec2i draw, int color)
{
	int	i;

	i = draw.x;
	while (i < draw.y)
	{
		((int*)img->data)[x + (i * img->size_line)] = color;
		i++;
	}
}
