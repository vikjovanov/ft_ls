/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 08:26:23 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 18:29:07 by vjovanov         ###   ########.fr       */
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
/*
int main(int argc, char **argv)
{
	char	buf;
	char	*buff;
	int		buf_size;

	printf("%zu\n", readlink(argv[1], buff, sizeof(buff)));
	exit(1);
	if (argc != 1)
	{
		if ((buf_size = (int)readlink(argv[1], buf, sizeof(buf))) < 0)
			perror("readlink() : ");
		else
		{
			buf[buf_size] = '\0';
			printf("%s\n", buf);
		}
	}
}
*/
/*
t_file	*move_front_file(t_file *lst_file, t_file *element)
{
	t_file	*tmp;
	t_file	*previous;

	tmp = lst_file;
	while (tmp != element)
	{
		if (tmp == element)
			break ;
		previous = tmp;
		tmp = tmp->next;
	}
	previous->next = tmp->next;
	element->next = lst_file;
	//printf("%zu\n", length_file(element));
	//display_lst_file(element);
	//exit(EXIT_FAILURE);
	return (element);
}

void	test()
{
	t_file	*node1;
	t_file	*node2;
	t_file	*node3;
	t_file	*tmp;

	node1 = malloc(sizeof(t_file));
	node2 = malloc(sizeof(t_file));
	node1->next = node2;
	node2->next = NULL;
	node1->modif_timestamps = 1547917757;
	node2->modif_timestamps = 1547917756;
	node3->modif_timestamps = 1547917756;
	tmp = node1;
	display_lst_file(tmp);
	tmp = move_front_file(tmp, node2);
	display_lst_file(tmp);

}

int main()
{
	test();
	return 0;
}
*/

int 	main(int argc, char **argv)
{
	struct stat v_file;
	struct passwd *pass_file;
	struct group *group_file;
	int i;
	time_t timer;

	if (argc < 2)
		return 0;	
	if (lstat(argv[1], &v_file) == -1)
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
	printf("time : %ld\n", v_file.st_mtime);


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