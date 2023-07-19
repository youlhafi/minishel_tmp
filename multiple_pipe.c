/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:50:02 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/17 14:14:48 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creat_pipe(t_pip *p)
{
	int	i;

	i = 0;
	p->fd_pipe = malloc(sizeof(int) * (2 * (p->nb_cmd - 1)));
	if (!p->fd_pipe)
		exit(EXIT_FAILURE);
	while (i < (2 * (p->nb_cmd - 1)) - 1)
	{
		if (pipe(&p->fd_pipe[i * 2]) == -1)
		{
			free(p->fd_pipe);
		}
		i++;
	}
}

void	ft_closefd(t_pip *p)
{
	int	i;

	i = 0;
	while (i < 2 * (p->nb_cmd - 1))
	{
		close(p->fd_pipe[i]);
		i++;
	}
}

void	ft_child(t_pip *p, char *cmd, t_cmd *cmds)
{
	if (p->child[p->i] == 0)
	{
		if (status != 0)
			exit(status);
		if (p->i == 0)
		{
			first_dup(p, cmds);
		}
		else if (p->i == p->nb_cmd - 1)
		{
			last_dup(p, cmds);
		}
		else
		{
			midle_dup(p, cmds);
		}
		ft_closefd(p);
		exec_cmd(p, cmd, cmds);
		close_fd(p);
		if (if_builtins(cmd))
			exit(status);
	}
}

void	parent_wait(t_pip *p, int i)
{
	int	j;

	ft_closefd(p);
	if (p->if_here_doc)
		unlink(".tmp_file");
	j = 0;
	while (j <= i)
	{
		waitpid(p->child[j], &status, 0);
		j++;
	}
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
	}
}

void	multiple_pipe(t_pip *p, t_cmd *cmds, int i)
{
	int	count;

	count = i;
	creat_pipe(p);
	p->i = -1;
	p->if_here_doc = 0;
	p->child = malloc(sizeof(pid_t) * p->nb_cmd);
	while (count > 0 && cmds)
	{
		init_p(p , cmds);
		p->i++;
		if (cmds->cmd && status == 0)
		{
			status = check_cmd(p, cmds->cmd, p->envp, cmds);
			p->child[p->i] = fork();
			ft_child(p, cmds->cmd, cmds);
			if (!if_builtins(cmds->cmd) && p->cmd)
				free(p->cmd);
		}
		count--;
		cmds = cmds->next;
	}
	parent_wait(p, p->i);
	free(p->child);
}
