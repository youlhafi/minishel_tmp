/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:09:39 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/15 11:52:04 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(int read, int write)
{
	dup2(read, 0);
	dup2(write, 1);
}

void	first_dup(t_pip *p, t_cmd *cmds)
{
	if (p->sign_out == -1)
		ft_dup(p->fd_in, p->fd_out);
	else
		ft_dup(p->fd_in, p->fd_pipe[1]);
}

void	last_dup(t_pip *p, t_cmd *cmds)
{
	if (p->sign_in == -1)
		ft_dup(p->fd_in, p->fd_out);
	else
		ft_dup(p->fd_pipe[2 * p->i - 2], p->fd_out);
}

void	midle_dup(t_pip *p, t_cmd *cmds)
{
	if (p->sign_out == -1 && p->sign_in == -1)
		ft_dup(p->fd_in, p->fd_out);
	else
	{
		if (p->sign_out == -1)
			ft_dup(p->fd_pipe[2 * p->i - 2], p->fd_out);
		else if (p->sign_in == -1)
			ft_dup(p->fd_in, p->fd_pipe[2 * p->i + 1]);
		else
			ft_dup(p->fd_pipe[2 * p->i - 2], p->fd_pipe[2 * p->i + 1]);
	}
}
