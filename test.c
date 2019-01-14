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
#include <grp.h>
#include <time.h>
#include "ft_printf.h"
#include "ft_ls.h"


int 	main(int argc, char **argv)
{
	struct stat v_file;
	struct passwd *pass_file;
	struct group *group_file;
	int i;
	time_t timer;

	if (argc < 2)
		return 0;	
	if (stat(argv[1], &v_file) == -1)
	{
		perror("stat : ");
		return (0);
	}
	i = -1;

	pass_file = getpwuid(v_file.st_uid);
	group_file = getgrgid(v_file.st_gid);
	printf("id device : %d\n", v_file.st_dev);
	printf("inode numb: %llu\n", v_file.st_ino);
	printf("mode type : %d\n", v_file.st_mode); //convertir en binaire pour recuperer valeurs
	printf("nb of link: %d\n", v_file.st_nlink);
	printf("used id ow: %d\n", v_file.st_uid);
	printf("\tusername  : %s\n", pass_file->pw_name);
	printf("\tuser passw: %s\n", pass_file->pw_passwd);
	printf("\tuser id   : %d\n", pass_file->pw_uid);
	printf("\tgroup id  : %d\n", pass_file->pw_gid);
	printf("\tuser info : %s\n", pass_file->pw_gecos);
	printf("\thome direc: %s\n", pass_file->pw_dir);
	printf("\tshell prog: %s\n", pass_file->pw_shell);
	printf("group id  : %d\n", v_file.st_gid);
	printf("\tgroup name   : %s\n", group_file->gr_name);
	printf("\tgroup passwd : %s\n", group_file->gr_passwd);
	printf("\tgroup ID     : %u\n", group_file->gr_gid);
	printf("\tgroup members:\n");
	while (group_file->gr_mem[++i] != NULL)
		printf("\t\tmember name: %s\n", group_file->gr_mem[i]);
	printf("id spe fil: %d\n", v_file.st_rdev);
	printf("total size: %lld\n", v_file.st_size);
	printf("block size: %d\n", v_file.st_blksize);
	printf("nb 512 all: %lld\n", v_file.st_blocks);
	printf("timestamps: %ld\n", time(&timer));
	printf("date times: %s\n", ctime(&timer)); //format de date constamment identique
}

/*
int		main()
{
	t_dir *dir;
	t_dir *tmp;

	dir = new_dir();
	dir = insert_back_dir(dir, "u/", "libft/");
	dir = insert_front_dir(dir, "libft/", "srcs/");
	dir = insert_front_dir(dir, "srcs/", NULL);
	dir = insert_back_dir(dir, "incl/", "libft/");
	dir = insert_back_dir(dir, "p/", "libft/");
	tmp = dir;
	printf("AVANT DELETE : \n");
	while (dir != NULL)
	{
		printf("pathname: %s\n", dir->pathname);
		printf("parent: %s\n", dir->parent);
		printf("========================\n");
		dir = dir->next;
	}
	dir = tmp;
	dir = del_back_dir(dir);
	tmp = dir;
	printf("\n\n\n");
	while (dir != NULL)
	{
		printf("pathname: %s\n", dir->pathname);
		printf("parent: %s\n", dir->parent);
		printf("========================\n");
		dir = dir->next;
	}
	dir = tmp;
	dir = del_front_dir(dir);
	tmp = dir;
	printf("\n\n\n");
	while (dir != NULL)
	{
		printf("pathname: %s\n", dir->pathname);
		printf("parent: %s\n", dir->parent);
		printf("========================\n");
		dir = dir->next;
	}
	dir = tmp;
	dir = clear_dir(dir);
	tmp = dir;
	printf("\n\n\n");
	printf("SUPP\n\n\n");
	while (dir != NULL)
	{
		printf("pathname: %s\n", dir->pathname);
		printf("parent: %s\n", dir->parent);
		printf("========================\n");
		dir = dir->next;
	}
	dir = new_dir();
	dir = insert_back_dir(dir, "u/", "libft/");
	dir = insert_front_dir(dir, "libft/", "srcs/");
	dir = insert_front_dir(dir, "srcs/", NULL);
	dir = insert_back_dir(dir, "incl/", "libft/");
	dir = insert_back_dir(dir, "p/", "libft/");
	tmp = dir;
	printf("AVANT DELETE : \n");
	while (dir != NULL)
	{
		printf("pathname: %s\n", dir->pathname);
		printf("parent: %s\n", dir->parent);
		printf("========================\n");
		dir = dir->next;
	}
	dir = tmp;
	printf("SIZE: %zu\n", length_dir(dir));
	return 0;
}
*/