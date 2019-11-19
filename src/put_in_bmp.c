/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:56:28 by niduches          #+#    #+#             */
/*   Updated: 2019/11/19 23:31:59 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cube3d.h"

#define	swap_endian(num) (((num>>24)&0xff) | \
                    ((num<<8)&0xff0000) | \
                    ((num>>8)&0xff00) | \
                    ((num<<24)&0xff000000))

#define BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

void	put_bitmap_header(t_tex *img, int fd, int padding_size)
{
	int				file_size;
	int				i;
	unsigned char	header[FILE_HEADER_SIZE];

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE +
(BYTES_PER_PIXEL * img->size.x + padding_size) * img->size.y;
	i = 0;
	while (i < FILE_HEADER_SIZE)
		header[i++] = 0;
	header[0] = 'B';
	header[1] = 'M';
	header[2] = (unsigned char)file_size;
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	write(fd, header, FILE_HEADER_SIZE);
}

void	put_info_header(t_tex *img, int fd)
{
	int				i;
	unsigned char	header[INFO_HEADER_SIZE];

	i = 0;
	while (i < INFO_HEADER_SIZE)
		header[i++] = 0;
	header[0] = (unsigned char)INFO_HEADER_SIZE;
	header[4] = (unsigned char)img->size.x;
	header[5] = (unsigned char)(img->size.x >> 8);
	header[6] = (unsigned char)(img->size.x >> 16);
	header[7] = (unsigned char)(img->size.x >> 24);
	header[8] = (unsigned char)img->size.y;
	header[9] = (unsigned char)(img->size.y >> 8);
	header[10] = (unsigned char)(img->size.y >> 16);
	header[11] = (unsigned char)(img->size.y >> 24);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
	write(fd, header, INFO_HEADER_SIZE);
}

void	put_pixels(t_tex *img, int fd, int padding_size)
{
	int				i;
	int				j;
	unsigned int	tmp;
	unsigned char	padding[3];

	i = 0;
	while (i < 3)
		padding[i++] = 0;
	i = img->size.y - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < img->size.x)
		{
			tmp = ((unsigned int*)img->data)[j + (i * img->size_line)];
			write(fd, &tmp, 3);
			j++;
		}
		write(fd, padding, padding_size);
		i--;
	}
}

int		put_in_bmp(t_tex *img)
{
	int				fd;
	int				padding_size;

	if ((fd = open("deepthought.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)) < 1)
		return (0);
	padding_size = (4 - (img->size.x * 4) % 4) % 4;
	put_bitmap_header(img, fd, padding_size);
	put_info_header(img, fd);
	put_pixels(img, fd, padding_size);
	close(fd);
	return (1);
}
