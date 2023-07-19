/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:33:03 by youlhafi          #+#    #+#             */
/*   Updated: 2023/07/15 11:33:13 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_p(t_pip *p, t_cmd *cmds)
{
		status = 0;
		p->sign_in = 0;
		p->sign_out = 0;
		p->fd_in = 0;
		p->fd_out = 1;
		status = open_files(p, cmds);
		p->std_in = dup(0);
		p->std_out = dup(1);
}