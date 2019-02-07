/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 08:39:00 by vjovanov          #+#    #+#             */
/*   Updated: 2019/01/20 21:17:07 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/acl.h>
# include "../libft/includes/libft.h"

# define PARAM_L 1
# define PARAM_R 2
# define PARAM_A 4
# define PARAM_RR 8
# define PARAM_T 16
# define ACCEPTED_PARAMS "lraRt"

# define MAX_LENGTH_FILENAME 4096

# define MINORBITS        24
# define MINORMASK        16777215

typedef struct		s_file
{
	char			file_type;
	int				permission;
	int				has_xattr;
	int				has_acl;
	int				number_of_link;
	char			*owner_name;
	char			*group_name;
	long			size_byte;
	unsigned int	major;
	unsigned int	minor;
	time_t			modif_timestamps;
	char			*modif_month;
	char			*modif_day;
	char			*modif_hours;
	char			*modif_years;
	char			*symlink;
	long long		block_512kb;
	char			*pathname;
	struct s_file	*next;
}					t_file;

typedef struct		s_dir
{
	char			*parent;
	char			*pathname;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_field
{
	int				n_link;
	int				user_name;
	int				group_name;
	int				size_byte;
	int				major;
	int				modif_hy;
}					t_field;

/*
** char params
** bit 1 : -l
** bit 2 : -r
** bit 4 : -a
** bit 8 : -R
** bit 16: -t
*/

typedef struct		s_global
{
	char			params;
	t_file			*lst_file;
	t_dir			*lst_dir;
}					t_global;

extern t_global g_global;

# define LST_DIR (g_global.lst_dir)
# define LST_FILE (g_global.lst_file)
# define PARAMS (g_global.params)

/*
** error
*/

void				no_such_error(const char *format);
void				generic_error(const char *error_element);

/*
** arg_checker
*/

int					arg_checker(int argc, char **argv);

/*
** generic_func
*/

long				ft_exp_l(long n, int exp);
void				exit_failure(void);
int 				free_file(t_file *path);

/*
** lst_dir
*/

t_dir				*new_dir(void);
t_dir				*insert_child_dir(t_dir *lst_dir, t_dir	*new_dirs);
t_dir				*fill_lst_dir(t_file *lst_file, t_dir *lst_dir);
t_dir				*insert_front_dir(t_dir *dir, char *path, char *parent);
t_dir				*insert_back_dir(t_dir *dir, char *path, char *parent);

int					is_empty_dir(t_dir *dir);
t_dir				*del_back_dir(t_dir *dir);
t_dir				*del_front_dir(t_dir *dir);
t_dir				*clear_dir(t_dir *dir);
size_t				length_dir(t_dir *dir);

/*
** lst_file
*/

t_file				*new_file(void);
t_file				*fill_link(t_file *new, struct stat *file, char *file_name,
	char *path);
t_file				*insert_back_file(t_file *lst_file, struct stat *file,
	char *file_name, char *path);
t_file				*move_front_file(t_file *lst_file, t_file *element);

int					is_empty_file(t_file *file);
t_file				*del_back_file(t_file *file);
t_file				*del_front_file(t_file *file);
t_file				*clear_file(t_file *file);
size_t				length_file(t_file *file);

int					fill_xattr(char *path, char file_type);
char				set_file_type(struct stat *file);
char				*set_symlink(char *path, char *name_file);
int					fill_last_modif(t_file *new, struct stat *file);
void				set_major_minor(t_file *new, struct stat *file);

/*
** order
*/

char				**order_by_lexic(char **str);
t_file				*lst_order_file(t_file *lst_file);
t_file				*lst_order_by_time(t_file *lst_file);

/*
** print
*/

t_file				*dispatch_print(t_file *lst_file, int print_mult_dir,
	int print_newline);
t_field				*find_min_field_width(t_file *file);
long long			total_block(t_file *lst_file);

int					recurse_nav(int multi_dir);

#endif
