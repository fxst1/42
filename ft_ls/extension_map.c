/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:54:53 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 01:54:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	init_extension_map_audio2(t_map **m)
{
	ft_mapadd_begin(m, ft_mapnew(".ogm", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".mp4", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".mp4v", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".vob", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".qt", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".nuv", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".wmv", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".asf", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".rm", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".rmvb", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".flc", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".avi", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".fli", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".flv", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".gl", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".dl", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".xcf", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".xwd", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".yuv", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".cgm", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".emf", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".axv", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".anx", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".ogv", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".ogx", "01;35"));
}

void	init_extension_map_audio1(t_map **m)
{
	ft_mapadd_begin(m, ft_mapnew(".jpg", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".jpeg", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".gif", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".bmp", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".pbm", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".pgm", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".ppm", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".tga", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".xbm", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".xpm", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".tif", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".tiff", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".png", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".svg", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".svgz", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".mng", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".pcx", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".mov", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".mpg", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".mpeg", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".m2v", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".mkv", "01;35"));
	ft_mapadd_begin(m, ft_mapnew(".webm", "01;35"));
}

void	init_extension_map_video(t_map **m)
{
	ft_mapadd_begin(m, ft_mapnew(".rar", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".ace", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".acc", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".au", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".flac", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".mid", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".midi", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".mka", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".mp3", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".mpc", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".ogg", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".ra", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".wav", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".axa", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".oga", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".spx", "00;36"));
	ft_mapadd_begin(m, ft_mapnew(".xspf", "00;36"));
}

void	init_extension_map_archive(t_map **m)
{
	ft_mapadd_begin(m, ft_mapnew(".tar", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".tgz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".arj", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".taz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".lzh", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".lzma", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".tlz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".txz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".zip", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".z", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".Z", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".dz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".gz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".lz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".lz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".bz2", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".bz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".tbz2", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".tz", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".deb", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".rpm", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".jar", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".war", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".ear", "01;31"));
	ft_mapadd_begin(m, ft_mapnew(".sar", "01;31"));
}

t_map	*init_extension_map(void)
{
	t_map	*m;

	m = NULL;
	init_extension_map_archive(&m);
	init_extension_map_video(&m);
	init_extension_map_audio1(&m);
	init_extension_map_audio2(&m);
	ft_mapadd_begin(&m, ft_mapnew(".zoo", "01;31"));
	ft_mapadd_begin(&m, ft_mapnew(".cpio", "01;31"));
	ft_mapadd_begin(&m, ft_mapnew(".7z", "01;31"));
	ft_mapadd_begin(&m, ft_mapnew(".rz", "01;31"));
	ft_mapadd_begin(&m, ft_mapnew(".cmd", "01;32"));
	ft_mapadd_begin(&m, ft_mapnew(".exe", "01;32"));
	ft_mapadd_begin(&m, ft_mapnew(".com", "01;32"));
	ft_mapadd_begin(&m, ft_mapnew(".btm", "01;32"));
	ft_mapadd_begin(&m, ft_mapnew(".sh", "01;32"));
	ft_mapadd_begin(&m, ft_mapnew(".csh", "01;32"));
	ft_mapadd_begin(&m, ft_mapnew(".c", "3;01;33"));
	ft_mapadd_begin(&m, ft_mapnew(".java", "00;33"));
	ft_mapadd_begin(&m, ft_mapnew(".h", "4;6;01;33"));
	ft_mapadd_begin(&m, ft_mapnew(".pdf", "01;35"));
	ft_mapadd_begin(&m, ft_mapnew(".trace", "00;33"));
	ft_mapadd_begin(&m, ft_mapnew(".fdf", "00;33"));
	ft_mapadd_begin(&m, ft_mapnew(".o", "00;33"));
	return (m);
}
