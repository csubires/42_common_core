/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:44:53 by csubires          #+#    #+#             */
/*   Updated: 2024/11/30 10:22:36 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strreplace(char *str, int start, int end, char *substr)
{
	char	*pre_str;
	char	*pos_str;
	char	*replace;

	pre_str = ft_substr(str, 0, start);
	pos_str = ft_substr(str, end, (ft_strlen(str) - end));
	replace = ft_strconcat(3, pre_str, substr, pos_str);
	free(pre_str);
	free(pos_str);
	return (replace);
}

static int	is_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

static void	empty_value(t_shell *shell, int *x, char *key)
{
	char	*tmp_str;

	if (!ft_strcmp(key, "?"))
	{
		*x += 2;
		free(key);
		return ;
	}
	tmp_str = ft_strreplace(shell->input, *x, (ft_strlen(key) + *x + 1), "");
	free(shell->input);
	shell->input = tmp_str;
	free(key);
}

static char	*trim_env_key(char *str)
{
	int		x;
	char	*key;

	x = 0;
	key = 0;
	while (ft_isprint(str[x]) && !ft_isspace(str[x]) \
	&& !is_quotes(str[x]) && str[x] != '$' && str[x] != ';')
		x++;
	if (x)
		key = ft_substr(str, 0, x);
	return (key);
}

void	expand_envp(t_shell *shell, int *x)
{
	char	*key;
	char	*value;

	value = 0;
	key = trim_env_key(shell->input + *x + 1);
	if (!key)
	{
		(*x)++;
		free(key);
		return ;
	}
	if (key && key[0] == '?')
		value = ft_itoa(shell->exit_stat);
	if (key && !value && !is_quotes(key[0]))
		value = get_env_value(shell->env_list, key);
	if (!value)
		empty_value(shell, x, key);
	else
		replace_value(shell, x, key, value);
}
