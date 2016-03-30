/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 05:17:12 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 05:17:15 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OS_H
# define OS_H
# define UNKNOWN_OS 0
# define WINDOWS_OS 1
# define UNIX_OS 2
# define MAC_OS 3
# if defined (_WIN32) || defined (WIN32) || defined (__WIN32__)
#  define OS_FT WINDOWS_OS
#  define ARCH_FT 32
#  define PATH_SEPARATOR "\\"
#  define PATH_SEPARATOR_LEN 1
# elif defined (_WIN64) || defined (WIN64) || defined (__WIN64__)
#  define OS_FT WINDOWS_OS
#  define ARCH_FT 64
#  define PATH_SEPARATOR "/"
#  define PATH_SEPARATOR_LEN 1
# elif defined (__APPLE__) || defined (__MAC__)
#  define OS_FT MAC_OS
#  define ARCH_FT 64
#  define PATH_SEPARATOR "/"
#  define PATH_SEPARATOR_LEN 1
# elif defined (__unix__) || defined (unix)
#  define OS_FT UNIX_OS
#  define ARCH_FT 64
#  define PATH_SEPARATOR "/"
#  define PATH_SEPARATOR_LEN 1
# else
#  define OS_FT UNKNOWN_OS
#  define ARCH_FT 0
#  define PATH_SEPARATOR "\0"
#  define PATH_SEPARATOR_LEN 0
# endif
#endif
