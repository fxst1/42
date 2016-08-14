/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 05:12:26 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 05:12:27 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H
# define DEFAULT "0"
# define CURSOR_UP "\e[0;0H"
# define CLEAR "\033c"
# define INCR_BOLD "1"
# define DECR_BOLD "2"
# define RESET_BOLD "22"
# define ENABLE_ITALIC "3"
# define DISABLE_ITALIC "23"
# define ENABLE_UNDERLINE "4"
# define DISABLE_UNDERLINE "24"
# define SLOW_BLINK "5"
# define RAPID_BLINK "6"
# define DISABLE_BLINK "25"
# define ENABLE_REVERSE "7"
# define DISABLE_REVERSE "27"
# define ENABLE_CONCEAL "8"
# define DISABLE_CONCEAL "28"
# define ENABLE_CROSSED "9"
# define DISABLE_CROSSED "29"
# define DEFAULT_FONT "10"
# define FRAKTUR_FONT "20"
# define RESET_FONT "23"
# define TEXT_COLOR "38"
# define DEFAULT_TEXT_COLOR "37;0"
# define BACK_COLOR "48"
# define DEFAULT_BACK_COLOR "39;0"
# define ENABLE_FRAMED "51"
# define DISABLE_FRAMED "54"
# define ENABLE_ENCIRCLED "52"
# define DISABLE_ENCIRCLED DISABLE_FRAMED
# define ENABLE_OVERLINE "53"
# define DISABLE_OVERLINE "55"
# define RESET_COLOR "39;37"
# define BLACK "30"
# define RED "31"
# define GREEN "32"
# define BROWN "33"
# define BLUE "34"
# define MAGENTA "35"
# define CYAN "36"
# define GREY "37"
# define LIGHT_COLOR "01;"
# define LIGHTBLACK "01;30"
# define LIGHTRED "01;31"
# define LIGHTGREEN "01;32"
# define LIGHTBROWN "01;33"
# define LIGHTBLUE "01;34"
# define LIGHTMAGENTA "01;35"
# define LIGHTCYAN "01;36"
# define LIGHTGREY "01;37"
# define DARK_COLOR "22"
# define DARKBLACK "22;30"
# define DARKRED "22;31"
# define DARKGREEN "22;32"
# define DARKBROWN "22;33"
# define DARKBLUE "22;34"
# define DARKMAGENTA "22;35"
# define DARKCYAN "22;36"
# define DARKGREY "22;37"
# define RESET "\x1B[0m"
#endif
