/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:30:22 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/17 17:41:22 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	ft_free_token(t_list *token)
{
	t_list	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}

void	ft_free_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			ft_free_str(tmp->args);
		if (tmp->files)
			ft_free_str(tmp->files);
		if (tmp->type)
			ft_free_str(tmp->type);
		if (tmp->type)
			ft_free_str(tmp->type_file);
		if (tmp->herdoc_lim)
			free(tmp->herdoc_lim);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
