/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 10:53:26 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/11 10:53:29 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H
# include <libft/os.h>
# if (OS_FT == UNIX_OS)
#  define ECH 65307
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65363
#  define RIGHT 65361
#  define DIVIDE 65455
#  define MULT 65450
#  define PLUS 65451
#  define LESS 65453
#  define KEY_EDIT 101
#  define ONE 65436
#  define TWO 65433
#  define THREE 65435
#  define FOUR 65430
#  define FIVE 65437
#  define SIX 65432
#  define SEVEN 65429
#  define EIGHT 65431
#  define NINE 65434
#  define ZERO 65438
#  define TABULATION 65289
#  define KEY_A	97
#  define KEY_B	98
#  define KEY_C	99
#  define KEY_D	100
#  define KEY_E	101
#  define KEY_F	102
#  define KEY_G	103
#  define KEY_H	104
#  define KEY_I	105
#  define KEY_J	106
#  define KEY_K	107
#  define KEY_L 108
#  define KEY_M	109
#  define KEY_N	110
#  define KEY_O	111
#  define KEY_P	112
#  define KEY_Q	113
#  define KEY_R	114
#  define KEY_S	115
#  define KEY_T	116
#  define KEY_U	117
#  define KEY_V	118
#  define KEY_W	119
#  define KEY_X	120
#  define KEY_Y	121
#  define KEY_Z	122
# else
#  define ECH 53
#  define UP 126
#  define DOWN 125
#  define LEFT 124
#  define RIGHT 123
#  define DIVIDE 75
#  define MULT 67
#  define PLUS 69
#  define LESS 78
#  define POINT 65
#  define ONE 83
#  define TWO 84
#  define THREE 85
#  define FOUR 86
#  define FIVE 87
#  define SIX 88
#  define SEVEN 89
#  define EIGHT 91
#  define NINE 92
#  define ZERO 82
#  define TABULATION 65289
#  define KEY_A	0
#  define KEY_B	11
#  define KEY_C	8
#  define KEY_D	2
#  define KEY_E	14
#  define KEY_F	3
#  define KEY_G	5
#  define KEY_H	4
#  define KEY_I	34
#  define KEY_J	38
#  define KEY_K	40
#  define KEY_L	37
#  define KEY_M	46
#  define KEY_N	45
#  define KEY_O	31
#  define KEY_P	35
#  define KEY_Q	12
#  define KEY_R	15
#  define KEY_S	1
#  define KEY_T	17
#  define KEY_U	32
#  define KEY_V	9
#  define KEY_W	13
#  define KEY_X	7
#  define KEY_Y	16
#  define KEY_Z	6
# endif
#endif
