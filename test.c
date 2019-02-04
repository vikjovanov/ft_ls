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


/*
  Copyright (C) 2009  Andreas Gruenbacher <agruen@suse.de>

  This program is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/acl.h>

const char *progname;

int main(int argc, char *argv[])
{
	int n, ret = 0;

	progname = basename(argv[0]);

	if (argc == 1) {
		printf("%s -- get access control lists of files\n"
			"Usage: %s file ...\n",
			progname, progname);
		return 1;
	}

	for (n = 1; n < argc; n++) {
		struct stat st;
		acl_t acl, default_acl;
		char *acl_text, *default_acl_text, *token;
		
		if (stat(argv[n], &st) != 0) {
			fprintf(stderr, "%s: %s: %s\n",
				progname, argv[n], strerror(errno));
			ret = 1;
			continue;
		}

		acl = acl_get_file(argv[n], ACL_TYPE_ACCESS);
		if (acl == NULL) {
			fprintf(stderr, "%s: getting acl of %s: %s\n",
				progname, argv[n], strerror(errno));
			ret = 1;
			continue;
		}
		acl_text = acl_to_text(acl, NULL);
		acl_free(acl);

		if (S_ISDIR(st.st_mode)) {
			default_acl = acl_get_file(argv[n], ACL_TYPE_DEFAULT);
			if (default_acl == NULL) {
				acl_free(acl_text);
				fprintf(stderr, "%s: getting default acl "
					"of %s: %s\n", progname, argv[n],
					strerror(errno));
				ret = 1;
				continue;
			}
			default_acl_text = acl_to_text(default_acl, NULL);
			acl_free(default_acl);
		}

		printf("# file: %s\n"
		       "# owner: %d\n"
		       "# group: %d\n"
		       "%s",
			argv[n], st.st_uid, st.st_gid, acl_text);

		if (S_ISDIR(st.st_mode)) {
			token = strtok(default_acl_text, "\n");
			while (token) {
				printf("default:%s\n", token);
				token = strtok(NULL, "\n");
			}
			acl_free(default_acl_text);
		}
		printf("\n");

		acl_free(acl_text);
	}
	return ret;
}







//#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
/*#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	int fd1;
	int fd2;
	char *line1, *line2;
	long line;

	if (argc != 3)
		return 0;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	line = 0;
	while (get_next_line(fd1, &line1) == 1)
	{
		if (get_next_line(fd2, &line2) == 1)
		{
			if (!ft_strequ(line1, line2))
			{
				printf("%ld |ls   | %s\n", line, line1);
				printf("%ld |ft_ls| %s\n", line, line2);
				printf("\n");
			}
			free(line1);
			free(line2);
		}
		line++;
	}
}*/



/*

#define S_IFSHAD 45056

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


	char *list;
	size_t size = 0;;
	size = listxattr(argv[1], NULL, size, 0);
	list = (char*)malloc(sizeof(char) * size);
	size = listxattr(argv[1], list, size, 0);
	printf("LST = %s\n", list);

	pass_file = getpwuid(v_file.st_uid);
	group_file = getgrgid(v_file.st_gid);
	ft_printf("1UU : %#b\n", MINORMASK);
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
	//minor codé 20
	//printf("minor: %d\n", MINOR(v_file.st_rdev));
	//major codé 12
	//printf("major: %d\n", MAJOR(v_file.st_rdev));
	printf("total size: %lld\n", v_file.st_size);
	printf("block size: %d\n", v_file.st_blksize);
	printf("nb 512 all: %lld\n", v_file.st_blocks);
	printf("timestamps: %ld\n", time(&timer));
	printf("date times: %s\n", ctime(&timer)); //format de date constamment identique
	printf("time : %ld\n", v_file.st_mtime);


}
*/

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