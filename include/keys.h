/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:18:52 by niduches          #+#    #+#             */
/*   Updated: 2020/08/11 13:52:52 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __linux__

#  define K_A 'a'
#  define K_B 'b'
#  define K_C 'c'
#  define K_D 'd'
#  define K_E 'e'
#  define K_F 'f'
#  define K_G 'g'
#  define K_H 'h'
#  define K_I 'i'
#  define K_J 'j'
#  define K_K 'k'
#  define K_L 'l'
#  define K_M 'm'
#  define K_N 'n'
#  define K_O 'o'
#  define K_P 'p'
#  define K_Q 'q'
#  define K_R 'r'
#  define K_S 's'
#  define K_T 't'
#  define K_U 'u'
#  define K_V 'v'
#  define K_W 'w'
#  define K_X 'x'
#  define K_Y 'y'
#  define K_Z 'z'

#  define K_ESC 65307
#  define K_1 '1'
#  define K_2 '2'
#  define K_3 '3'
#  define K_4 '4'
#  define K_5 '5'
#  define K_6 '6'
#  define K_7 '7'
#  define K_8 '8'
#  define K_9 '9'
#  define K_0 '0'

#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define K_DOWN 65364
#  define K_UP 65362

#  define K_SPACE ' '
#  define K_SHIFT 65505

# else

#  define K_A 0
#  define K_B 11
#  define K_C 8
#  define K_D 2
#  define K_E 14
#  define K_F 3
#  define K_G 5
#  define K_H 4
#  define K_I 34
#  define K_J 38
#  define K_K 40
#  define K_L 37
#  define K_M 46
#  define K_N 45
#  define K_O 31
#  define K_P 35
#  define K_Q 12
#  define K_R 15
#  define K_S 1
#  define K_T 17
#  define K_U 32
#  define K_V 9
#  define K_W 13
#  define K_X 7
#  define K_Y 16
#  define K_Z 6

#  define K_ESC 53
#  define K_1 18
#  define K_2 19
#  define K_3 20
#  define K_4 21
#  define K_5 23
#  define K_6 22
#  define K_7 26
#  define K_8 28
#  define K_9 25
#  define K_0 29

#  define K_LEFT 123
#  define K_RIGHT 124
#  define K_DOWN 125
#  define K_UP 126

#  define K_SPACE 49
#  define K_SHIFT 257

# endif

#endif
