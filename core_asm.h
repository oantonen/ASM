/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_asm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:30:09 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/29 13:23:32 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_ASM_H
# define CORE_ASM_H

#include "/Users/oantonen/CLionProjects/core/libft/includes/hprintf.h"
#include "/Users/oantonen/CLionProjects/core/libft/includes/libft.h"
#include "/Users/oantonen/CLionProjects/core/libft/includes/get_next_line.h"
#include "split_line.h"

#include <stdio.h>//
#include <stdbool.h>

typedef struct  s_info
{
	bool		name;
	bool		coom;
	t_list		*fl_lst;


}				t_info;

typedef struct	s_lbl
{
	char 		*name;
	t_list		*line;
}				t_lbl;

typedef struct  s_fls
{
	char		isname;
	char		iscmnt;
	char		*name;
	char		*cmnt;
	t_list		*lbls;
	t_list		*lines;
	t_list		*instr;

}				t_fls;

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define INIT_INFO				info = {0, 0, NULL};
# define INIT_FILE				{0, 0, NULL, NULL, NULL, NULL};
# define PROG_NAME_LENGTH       (128)
# define COMMENT_LENGTH         (2048)
# define COREWAR_EXEC_MAGIC     0xea83f3


int     save_file(t_info *info, int fd);
void    check_cmnt(t_fls *file, t_list **ptr);
void	print_errors(int err);
void	rotate_str(char *s, char *chars);
bool	check_header(t_fls *file);
void	split_labels(t_fls *file, t_list *instr);
int		check_empty(char *str);


#endif
