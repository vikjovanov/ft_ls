/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 09:23:10 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/08 09:23:11 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		display_dir(char *pathname)
{
	DIR *dir;
	struct dirent *buf;

	if ((dir = opendir(pathname)) == NULL)
		perror("opendidr() error");
	else
	{
		while ((buf = readdir(dir)) != NULL)
			 ft_printf("%s\n", buf->d_name);
	}
	closedir(dir);
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		display_dir("./");
	else if (argc == 2)
		display_dir(argv[1]);
	return (0);
}