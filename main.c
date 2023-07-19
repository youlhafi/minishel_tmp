/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:43:33 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/17 18:54:28 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env1(char **env)
{
	char	**str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	str = NULL;
	while (env[count])
		count++;
	str = malloc(sizeof(char *) * count + 1);
	if (!str)
		return NULL;
	i = 0;
	while (env[i])
	{
		str[i] = ft_strdup(env[i]);
		if (!str[i])
		{
			while (i > 0)
				free(str[--i]);
			free(str);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	*minishell(char *str)
{
	char	*dst;

	dst = NULL;
	int len = (ft_strlen(str) - 2);
	if (!dst)
		return (NULL);
	dst = ft_substr(str, 2, len);
	return (dst);    
}

int	if_error(t_list *new, t_cmd *cmd_list)
{
	if (parsing(&new) || parse_quotes(&new))
	{
		ft_error("syntax error", 258, NULL, NULL);
		ft_free_token(new);
		return (1);
	}
    return (0);
}

void	ft_token(char *str, t_pip *p)
{
	t_cmd	*cmd_list;
	t_list	*new;
	t_list	*lst;
	char	**dst;
	int		i;

	i = 0;
	cmd_list = cmd(NULL);
	new = NULL;
	lst = NULL;
	dst = split_string(str, SPACE);
	while (dst[i])
		ft_add_back_token(&lst, ft_new_token(dst[i++]));
	new = ft_lex(&lst);
	if (if_error(new, cmd_list))
		return ;
	ft_env2(&new, p->envp);
	ft_quotes(&new);
	parse_input(cmd_list, &new, 0);
	check_pipe(p, cmd_list, p->envp);
	ft_free_token(new);
	ft_free_token(lst);
	ft_free_str(dst);
	ft_free_list(cmd_list);
}

char	**get_short_env()
{
	char	*pwd;
	char	*pwd1;
	char	*shlvl;
	char	*_;
	char	*envp;
	char	**ret;

	envp = NULL;
	pwd = ft_strdup("PWD=");
	pwd1 = getcwd(NULL, 0);
	pwd = ft_strjoin_get(pwd, pwd1);
	free(pwd1);
	shlvl = ft_strdup("SHLVL=1");
	_ = ft_strdup("_=/usr/bin/env");
	envp = ft_strjoinspace(envp, pwd);
	free(pwd);
	envp = ft_strjoinspace(envp, shlvl);
	free(shlvl);
	envp = ft_strjoinspace(envp, _);
	free(_);
	ret = ft_split(envp, ' ');
	free(envp);
	return (ret);
}

void	handle_ctrl_c(int i)
{
	if (i == SIGINT)
	{
		global.herdoc = 1;
		printf ("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		status = 1;
	}
}

void	handle_ctrl_b(int i)
{
	(void)i;
	return ;
}

void	main_shell(t_pip p)
{
	char	*str;

	while (1)
	{
		rl_on_new_line();
		str = readline("minishell>");
		if (str != NULL)
		{
			if (str[0])
			{
				ft_token(str, &p);
				add_history(str);
			}
			free(str);
		}
		if (!str)
		{
			printf("exit\n");
			exit(0);
		}
		if (p.if_exit == 1)
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_pip	p;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_b);
	// rl_catch_signals = 0;
	if (!getenv("PWD"))
		p.envp = get_short_env();
	else
		p.envp = get_env1(env);
	p.export = NULL;
	p.if_exit = 0;
	main_shell(p);
    
	return (status);
}
