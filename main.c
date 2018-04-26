/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/26 18:04:03 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

int		print_errors2(char err_type, char *token, char *err_str, int line)
{
	char	*err;

	if (err_type == 1)
		err = "Syntax error at token ";
	else if (err_type == 2)
		err = "Invalid argument for ";
	else if (err_type == 0)
		err = "";
	else if (err_type == 3)
		err = "Lexical error ";
	else if (err_type == 4)
		err = "Lexical error at NAME ";
	else if (err_type == 5)
		err = "Lexical error at COMMENT ";
	else if (err_type == 6)
		err = "Invalid instruction at token ";
	ft_printf("%s%s \"%s\" at line %d\n", err, token, err_str, line);
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

int		check_read_input(t_list **fl_lst, t_list **fl_err, int ac, char **av)
{
	int		fd;
	int		i;

	i = 1;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0)
			ft_printf("Error while opening file \"%s\"\n", av[i]);
		else
			return (save_file(fl_lst, fl_err, fd));
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_list	*fl_lst;
	t_list	*fl_err;
	int		ret;

	fl_lst = NULL;
	ret = check_read_input(&fl_lst, &fl_err, argc, argv);
	return (0);
}
