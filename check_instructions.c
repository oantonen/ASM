/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:58:36 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/19 15:31:59 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "op.h"

int 	check_indirect(char *arg, int i, int type)
{
	while (arg[i] && ft_isdigit(arg[i]))
			i++;
	if (arg[i] == '\0' && type == 1)
		return (2);
	else if (arg[i] == '\0' && type == 2)
		return (4);
	return (0);
}

int 	check_direct(char *arg, t_list *lbls)
{
	t_list	*ptr;

	ptr = lbls;
	if (arg[1] == LABEL_CHAR)
	{
		while (ptr)
		{
			if (ft_strequ(&arg[2], ((t_lbl*)ptr->content)->name))
				break;
			ptr = ptr->next;
		}
		if (ptr != NULL)
			return (2);
	}
	else
		return (check_indirect(&arg[1], 0, 1));
	return (0);
}

int 	identify_argtype(char *arg, t_list *lbls)
{
	int 	nb;

	nb = 0;
	ft_printf("arg=%s\n", arg);
	if (arg[0] == 'r')
	{
		nb = ft_atoi(&arg[1]); //atoi+itoa
		if (nb >= 1 && nb < REG_NUMBER && ft_strequ(&arg[1], ft_itoa(nb)))
			return (1);
	}
	else if (arg[0] == DIRECT_CHAR)
		return (check_direct(arg, lbls));
	else if (ft_isdigit(arg[0]))
		return (check_indirect(arg, 0, 2));
	return (0);
}

int 	check_args(char *ins, t_list *args, char arg_type[3], t_list *lbls)
{
	t_list	*ptr;
	int 	arg;
	int 	i;

	i = 0;
	ptr = args;
	while (ptr)
	{
		if ((arg = identify_argtype((char*)ptr->content, lbls)) == 0)
			print_errors(52);
		// ft_printf("arg_nb=%d\n", arg);
		// ft_printf("ISREG=%d\n", ISREG);
		// ft_printf("ISDIR=%d\n", ISDIR);
		// ft_printf("ISIND=%d\n", ISIND);
		if (arg != ISREG && arg != ISDIR && arg != ISIND)
			print_errors(53);
		ptr = ptr->next;
		i++;
	}
	return (1);
}

int		check_opcode(t_spl *spltd)
{
	char	*ins;
	int 	i;

	ins = spltd->op_code;
	i = 0;
	if (ins == NULL)
		return (-1);
	while (g_optab[i].name)
	{
		if (ft_strequ(spltd->op_code, g_optab[i].name))
			break;
		i++;
	}
	ft_printf("spltd->q_arg=%d\n", spltd->q_arg);
	ft_printf("g_optab[i].q_arg=%d\n", g_optab[i].q_arg);
	if (i == 16)
		print_errors(50);
	else if (spltd->q_arg != g_optab[i].q_arg)
		print_errors(51);
	
	return (i);
}

int		check_instructions(t_fls *file, t_list *spltd, t_list *lbls)
{
	t_list	*ptr;
	t_spl	*line;
	int 	op_nb;

	ptr = spltd;
	while (ptr)
	{
		line = (t_spl*)ptr->content;
		op_nb = check_opcode(line);
		if (!g_is_err && op_nb != -1)
			op_nb = check_args(line->op_code, line->args, g_optab[op_nb].arg_type, lbls);
		// if (op_nb == 0)

		ptr = ptr->next;
	}
	return (1);
}
