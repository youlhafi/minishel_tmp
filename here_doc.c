/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:44 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/17 18:51:43 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_here_doc(t_pip *p, char *limter)
{
	char	*line;
	char	*save;
	int		fd_tmp;

	line = NULL;
	save = NULL;
	
	/*if (fd_tmp < 0)
		ft_perror("Infile");*/
	p->if_here_doc = 1;
	while (1)
	{
		write(1, "> ", 3);
		line = get_next_line(0);
		if (line == NULL)
			break;
		else if (global.herdoc)
			break ;
		if (ft_strncmp(limter, line, ft_strlen(limter)) == 0)
			break ;
		save = ft_strjoin_get(save, line);
		//write(fd_tmp, line, ft_strlen(line));
		//write(fd_tmp, "\n", 1);
		free(line);
	}
	fd_tmp = open(".tmp_file", O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd_tmp, save, ft_strlen(save));
	close(fd_tmp);
	free(line);
	p->fd_in = open(".tmp_file", O_RDONLY);
	if (p->fd_in < 0)
	{
		unlink(".tmp_file");
		//ft_msgerror("Infile");
	}
}