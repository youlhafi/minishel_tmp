/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:43:32 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/17 13:59:26 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_no_builtins(t_pip *p, t_cmd *cmds)
{
	pid_t	child;

	status = check_cmd(p, cmds->cmd, p->envp, cmds);
	if (status != 0)
	{
		close_fd(p);
		return ;
	}
	child = fork();
	if (child == 0)
	{
		if (status != 0)
			exit(status);
		ft_exec(p, cmds->cmd, p->envp, cmds);
	}
	close_fd(p);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	free(p->cmd);
}

void	dup_fd(t_pip *p, t_cmd *cmds)
{
	if (cmds->files[0])
	{
		if (p->sign_in == -1)
		{
				p->std_in = dup(0);
			dup2(p->fd_in, 0);
			close(p->fd_in);
		}
		else if (p->sign_out == -1)
		{
			p->std_out = dup(1);
			dup2(p->fd_out, 1);
			close(p->fd_out);
		}
	}
}

void	single_cmd(t_pip *p, t_cmd *cmds)
{
	pid_t	child;

	p->sign_in = 0;
	p->sign_out = 0;
	p->if_here_doc = 0;
	open_files(p, cmds);
	if (p->sign_in == 1 || p->sign_out == 1)
		return ;
	dup_fd(p, cmds);
	if (!cmds->cmd)
	{
		if (p->if_here_doc)
			unlink(".tmp_file");
		close_fd(p);
		return ;
	}
	if (if_builtins(cmds->cmd))
	{
		exec_builtins(p, cmds->cmd, cmds);
		close_fd(p);
	}
	else
		exec_no_builtins(p, cmds);
	if (p->if_here_doc)
		unlink(".tmp_file");
}
