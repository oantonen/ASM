/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:32:17 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/20 20:59:26 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

void	print_errors(int err)
{
	ft_printf("Error while reading. [%d]", err);
	exit (1);
}

int	print_errors2(char err_type, char *token, char *err_str, int line)
{
	char *err;

	if (err_type == 1)
		err = ft_strdup("Syntax error at token ");
	else if (err_type == 2)
		err = ft_strdup("Invalid argument for ");
	else if (err_type == 0)
		err = "";
	else if (err_type == 3)
		err = "Lexical error ";
	ft_printf("%s%s %s at line %d\n", err, token, err_str, line);
	g_is_err = 1;
	return (0);
}

void	asm_del_lst(t_list **begin)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = *begin;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(ptr2->content);
		free(ptr2);
	}
}

int		check_file(t_list *lbls, t_fls *file)
{
	check_header(file);
	check_instructions(file, file->spltd, lbls);
	return (0);
}

int		check_empty(char *str)
{
	char	*hash;

	hash = ft_strchr(str, '#');
	if (hash)
		*hash = '\0';
	while (*str)
	{
		if (!ft_strchr(" \t", *str))
			return (0);
		str++;
	}
	return (1);
}

// void	check_endline(int fd)
// {
// 	char	*buf;
// 	char	*big;
// 	char	*del_big;

// 	buf = (char*)ft_memalloc(101);
// 	lseek(fd, 0L, 0);
// 	big = NULL;
// 	while (read(fd, buf, 100) > 0)
// 	{
// 		if (big == NULL)
// 			big = ft_strdup(buf);
// 		else
// 		{
// 			del_big = big;
// 			big = ft_strjoin(big, buf);
// 			ft_strdel(&del_big);
// 		}
// 		ft_bzero(buf, 100);
// 	}	
// 	buf = ft_strrchr(big, '\n');
// 	if (!check_empty(buf + 1))
// 		print_errors(4);
// }

void	save_instruction(t_info *info, t_fls *file, int fd)
{
	char	*first;
	int		i;
	
	i = 0;
	while (get_next_line(fd, &first) > 0)
	{
		file->line++;
		if (!check_empty(first) && first[0] != '\0')
			ft_list_push_back(&file->instr, ft_lstnew(ft_strtrim(first), file->line));
		ft_strdel(&first);
		i++;
	}
	// check_endline(fd);
	if (i == 0 || !file->instr)
		print_errors2(0, "No instruction was found", "END", file->line);
	if (!g_is_err)
		split_lines(file, file->instr);
	if (!g_is_err)
		split_labels(file, file->instr);
	// t_list *ptr = file->instr;
	// while (ptr)
	// {
	// 	ft_printf("%s\n", ptr->content);
	// 	ptr = ptr->next;
	// }
}

void	save_header(t_fls *file, int fd)
{
	int			i;
	char		*s;
	char		*p;

	i = 0;
	while (i != 4 && get_next_line(fd, &s) > 0)
	{
		p = s;
		while (*p)
		{
			if (*p == '"')
				i++;
			p++;
		}
		ft_list_push_back(&(file->lines), ft_lstnew(s, 0));
		file->line++;
	}
	if (i != 4)
	{
		asm_del_lst(&file->lines);
		free(file);
		print_errors2(1, "[TOKEN]", "incomplete header structure", file->line);
	}
}

int		save_file(t_info *info, int fd)
{
	t_fls	*file;
	t_list	*ptr;
	
	file = (t_fls*)malloc(sizeof(t_fls));
	g_is_err = 0;
	*file = (t_fls){0, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0};
	save_header(file, fd);
	if (g_is_err == 0)
		check_header(file);
	if (g_is_err == 0)
		save_instruction(info, file, fd);
	if (g_is_err == 0)
		check_instructions(file, file->spltd, file->lbls);
	// ptr = file->instr;
	// while (ptr)
	// {
	// 	check_instr(file, (char*)ptr->content, file->lbls);
	// 	ptr = ptr->next;
	// }

	// if (check_file(file->lbls, file))
	// 	ft_lstadd(&(info->fl_lst), ft_lstnew(file, 0));
	// else
	// 	return (0);
	return (1);
}


