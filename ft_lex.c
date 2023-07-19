/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:14:27 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/17 17:47:17 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_case(char c, const char *s, char **res, int *i)
{
	int	rest;

	rest = 0;
	if ((c == '<' && s[1] == '<') || (c == '>' && s[1] == '>'))
	{
		res[*i] = ft_substr(s, 0, 2);
		(*i)++;
		rest += 2;
	}
	else if ((c == '|' || s[0] == '|') && s[0] == c)
	{
		res[*i] = ft_substr(s, 0, 1);
		(*i)++;
		rest += 1;
	}
	else
	{
		res[*i] = ft_substr(s, 0, 1);
		(*i)++;
		rest += 1;
	}
	return (rest);
}

static char	**ft_split_arg(const char *s, char c)
{
	int		i;
	int		len;
	char	**res;
	int		special;

	res = ft_calloc(ft_strlen(s) + 1, sizeof(char *));
	i = 0;
	while (*s)
	{
		len = 0;
		while (s[len] && s[len] != '<' && s[len] != '>' && s[len] != '|')
			len++;
		if (len > 0)
		{
			res[i++] = ft_substr(s, 0, len);
			s += len;
		}
		else
		{
			special = handle_special_case(c, s, res, &i);
			s += special;
		}
	}
	return (res);
}

int	into_quotes(char *str, char c)
{
	int		i;
	int		y;
	int		j;
	char	quote;

	i = 0;
	y = 0;
	j = 0;
	while (str[i] && !is_quote(str[i]))
		i++;
	if (str[i])
	{
		quote = str[i];
		j = i + 1;
		while (str[j] && str[j] != quote)
			j++;
		while (str[y] && str[y] != c)
			y++;
		if (y > i && y < j)
			return (1);
	}
	return (0);
}

void	add_lex(t_list **new, char *input, char c)
{
	char	**arg;
	int		i;

	arg = NULL;
	i = 0;
	if (into_quotes(input, c) == 0)
	{
		arg = ft_split_arg((const char *)input, c);
		while (arg[i])
			ft_add_back_token(new, ft_new_token(arg[i++]));
		ft_free_str(arg);
	}
	else
		ft_add_back_token(new, ft_new_token(input));
}

t_list	*ft_lex(t_list **lst)
{
	t_list	*tmp;
	t_list	*new;
	int		i;

	i = 0;
	new = NULL;
	tmp = (*lst);
	while (tmp)
	{
		if (ft_strchr((const char *)tmp->content, '>'))
			add_lex(&new, tmp->content, '>');
		else if (ft_strchr((const char *)tmp->content, '<'))
			add_lex(&new, tmp->content, '<');
		else if (ft_strchr((const char *)tmp->content, '|'))
			add_lex(&new, tmp->content, '|');
		else if (!ft_strcmp(tmp->content, "''")
			|| !ft_strcmp(tmp->content, "\"\""))
			tmp->content = ft_strdup("");
		else
			ft_add_back_token(&new, ft_new_token(tmp->content));
		tmp = tmp->next;
	}
	return (new);
}
