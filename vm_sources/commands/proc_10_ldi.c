/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:29:56 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/19 14:29:57 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

static void	parse_args(t_codes cod_b, int *arg, t_process *proc)
{
	if (cod_b.t[0] == TREG)
		arg[0] = proc->registry[arg[0]];
	else if (cod_b.t[0] == TIND)
		arg[0] = get_int(proc->pc + (short)(arg[0]) % IDX_MOD, 4);
	if (cod_b.t[1] == TREG)
		arg[1] = proc->registry[arg[1]];
}

static void	print_log(t_process *proc, int *arg)
{
	if (g_g.log_flag1)
	{
		ft_printf("P%5d | ldi %d %d r%d\n",
			proc->secret_num + 1, arg[0], arg[1], arg[2]);
		ft_printf("       | -> load from %d + %d = %d ",
			arg[0], arg[1], arg[0] + arg[1]);
		ft_printf("(with pc and mod %d)\n",
			proc->pc + (arg[0] + arg[1]) % IDX_MOD);
	}
}

void		proc_ldi(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			toskip;
	int			arg[3];

	cod_b = get_cod_b(&toskip, &proc, data);
	if (!cod_b.t[0] || (cod_b.t[1] != TDIR && cod_b.t[1] != TREG)
		|| cod_b.t[2] != TREG ||
		!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip) ||
		!parse_arg(cod_b.t[2], proc, &arg[2], &toskip))
	{
		print_move(proc, count_total_skip(cod_b, 1, 3, proc->label_size));
		proc->pc = set_pos(proc->pc +
			count_total_skip(cod_b, 1, 3, proc->label_size));
		return ;
	}
	parse_args(cod_b, arg, proc);
	proc->registry[arg[2]] = get_int(proc->pc +
		(arg[0] + arg[1]) % IDX_MOD, 4);
	print_log(proc, arg);
	print_move(proc, toskip);
	proc->pc = set_pos(proc->pc + toskip);
}
