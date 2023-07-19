/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:19:45 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/17 17:47:27 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_status(char *str)
{
	char	*dst;
	char	*tmp;
	int		i;

	dst = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "$?", 2))
		{
			tmp = ft_itoa(status);
			dst = ft_strjoin_get(dst, tmp);
			free(tmp);
			i += 2;
		}
		else
		{
			dst = ft_strjoinch(dst, str[i]);
			i++;
		}
	}
	return (dst);
}

t_cmd	*cmd(void *lst)
{
	t_cmd	*new;

	(void)lst;
	new = malloc(sizeof(t_cmd));
	new->cmd = NULL;
	new->args = malloc(sizeof(char *) * 20);
	new->files = malloc(sizeof(char *) * 20);
	new->type_file = malloc(sizeof(char *) * 20);
	new->type = malloc(sizeof(char *) * 20);
	new->herdoc_lim = NULL;
	new->next = NULL;
	return (new);
}

void	null_it(t_cmd *cmd, int i, int out)
{
	cmd->files[out] = NULL;
	cmd->type_file[out] = NULL;
	cmd->type[out] = NULL;
	cmd->args[i] = NULL;
}

void	parse_input(t_cmd *cmdList, t_list **new, int i)
{
	t_cmd	*current_cmd;
	t_list	*tmp;
	int		out;

	out = 0;
	current_cmd = cmdList;
	tmp = *new;
	while (tmp && tmp->content)
	{
		if (!current_cmd->cmd)
			command(current_cmd, tmp);
		if (tmp && tmp->content)
			arguments(current_cmd, &tmp, &i);
		redirection(current_cmd, &tmp, &out);
		if (tmp && (ft_strcmp(tmp->content, "|") == 0))
		{
			null_it(current_cmd, i, out);
			current_cmd->next = cmd(NULL);
			current_cmd = current_cmd->next;
			tmp = tmp->next;
			out = 0;
			i = 0;
		}
		if (!tmp)
			null_it(current_cmd, i, out);
	}
}