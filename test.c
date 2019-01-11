/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 08:26:23 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/07 08:26:24 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <sys/xattr.h>
#include <stdlib.h>
#include <string.h>
#include "ft_printf.h"
#include "ft_ls.h"

int		main()
{
	t_dir *dir;

	dir = new_dir();
	dir = insert_back_dir(dir, "u/", "libft/");
	dir = insert_front_dir(dir, "libft/", "srcs/");
	dir = insert_front_dir(dir, "srcs/", NULL);
	dir = insert_back_dir(dir, "incl/", "libft/");
	dir = insert_back_dir(dir, "p/", "libft/");

	while (dir != NULL)
	{
		printf("pathname: %s\n", dir->pathname);
		printf("parent: %s\n", dir->parent);
		printf("========================\n");
		dir = dir->next;
	}
	return 0;
}