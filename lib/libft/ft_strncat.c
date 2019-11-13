/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:18:33 by niduches          #+#    #+#             */
/*   Updated: 2019/10/10 15:19:56 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*my_strncat(char *dest, char const *src, int nb)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (dest[len])
		len++;
	while (i < nb && src[i] != '\0')
		dest[len + 1] = src[i];
	dest[len + i] = '\0';
	return (dest);
}
