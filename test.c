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

int		main()
{
	struct dirent *stru;
	DIR *dir;
	struct stat *buf;
	unsigned long size;

	buf = (struct stat*)malloc(sizeof(buf));

	stat("./test.c", buf);
	/*
	printf("dev_t: %lu\n", sizeof(dev_t));
	printf("ino_t: %lu\n", sizeof(ino_t));
	printf("mode_t: %lu\n", sizeof(mode_t));
	printf("nlink_t: %lu\n", sizeof(nlink_t));
	printf("uid_t: %lu\n", sizeof(uid_t));
	printf("gid_t: %lu\n", sizeof(gid_t));
	printf("blksize_t: %lu\n", sizeof(blksize_t));
	printf("blkcnt_t: %lu\n", sizeof(blkcnt_t));
	printf("time_t: %lu\n", sizeof(time_t));
	*/
	printf("    %u    %hu\n", buf->st_gid, buf->st_mode);

	if ((dir = opendir("./")) == NULL)
		perror("opendir() error");
	else
		while ((stru = readdir(dir)) != NULL)
		{
			printf("%s\n", stru->d_name);
		}
	closedir(dir);
	return 0;
}