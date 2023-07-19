/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:12:39 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/15 11:16:24 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_in_file(t_pip *p, char *file, char *type, char *lim)
{
	p->sign_in = -1;
	if (ft_strlen(file) == 0)
	{
		p->sign_in = 1;
		return (ft_error("ambiguous redirect", 1, file, NULL));
	}
	if (ft_strcmp(type, "R") == 0)
	{
		p->fd_in = open(file, O_RDONLY);
		if (p->fd_in < 0)
		{
			p->sign_in = 1;
			return (check_permission(file, 'r'));
		}
	}
	else if (ft_strcmp(type, "H") == 0)
	{
		ft_read_here_doc(p, lim);
	}
	return (0);
}

int	open_out_file(t_pip *p, char *file, char *type)
{
	p->sign_out = -1;
	if (ft_strlen(file) == 0)
	{
		p->sign_in = 1;
		return (ft_error("ambiguous redirect", 1, file, NULL));
	}
	if (ft_strcmp(type, "R") == 0)
	{
		p->fd_out = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (p->fd_out < 0)
		{
			p->sign_out = 1;
			return (check_permission(file, 'w'));
		}
	}
	else if (ft_strcmp(type, "H") == 0)
	{
		p->fd_out = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (p->fd_out < 0)
		{
			p->sign_out = 1;
			return (check_permission(file, 'w'));
		}
	}
	return (0);
}

int	open_files(t_pip *p, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds->files[0])
	{
		while (cmds->files[i])
		{
			if (ft_strcmp(cmds->type_file[i], "in") == 0)
			{
				status = open_in_file(p, cmds->files[i],
						cmds->type[i], cmds->herdoc_lim);
				if (status != 0)
					return (status);
			}
			else if (ft_strcmp(cmds->type_file[i], "out") == 0)
			{
				status = open_out_file(p, cmds->files[i], cmds->type[i]);
				if (status != 0)
					return (status);
			}
			i++;
		}
	}
	return (0);	
}

void	close_fd(t_pip *p)
{
	if (p->std_out != 1)
	{
		close(1);
		dup2(p->std_out, 1);
		close(p->std_out);
	}
	if (p->std_in != 0)
	{
		close(0);
		dup2(p->std_in, 0);
		close(p->std_in);
	}
}

