/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:58 by jesumore          #+#    #+#             */
/*   Updated: 2024/11/29 19:28:24 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_to_dllist_check(t_shell *shell)
{
	replace_with_envp(shell);
	if (shell->error)
		return (1);
	if (split_tokens(shell, (char *)shell->input) == 1)
	{
		print_error(1, shell, ERR_FIRST_QUOTE, 0);
		return (1);
	}
	if (!shell->token_list || !shell->token_list->data)
	{
		print_error(1, shell, ERR_TOKEN, 0);
		return (1);
	}
	return (0);
}

void	replace_value(t_shell *shell, int *x, char *key, char *value)
{
	char	*tmp_str;
	int		len;

	len = ft_strlen(value);
	tmp_str = ft_strreplace(shell->input, *x, \
	(ft_strlen(key) + *x + 1), value);
	free(shell->input);
	shell->input = tmp_str;
	if (key && key[0] == '?')
	{
		free(value);
		value = 0;
	}
	if (key)
	{
		free(key);
		key = 0;
	}
	*x += len;
}

int	check_double_quote(t_shell *shell)
{
	int		x;
	int		cdoble;
	int		csimple;

	x = 0;
	cdoble = 0;
	csimple = 0;
	while (shell->input[x])
	{
		if (shell->input[x] == '\'')
			csimple++;
		if (shell->input[x] == '\"')
			cdoble++;
		x++;
	}
	return (csimple % 2 != 0 || cdoble % 2 != 0);
}

void	repare_executable(t_exec *exec_cmd, t_dllist *tmp_list2)
{
	exec_cmd->executable = ft_strdup((char *)(tmp_list2)->data);
	if (exec_cmd->executable[ft_strlen(exec_cmd->executable) - 1] \
	== ' ')
	{
		exec_cmd->executable[ft_strlen(exec_cmd->executable) - 1] \
		= '\0';
		free(tmp_list2->data);
		tmp_list2->data = ft_strdup(exec_cmd->executable);
	}
}

void	set_redirect2(t_shell *shell, char *input, int *x)
{
	if (input[*x] == input[*x + 1])
	{
		token_to_dllist(shell, *x, *x + 2, ' ');
		*x += 1;
	}
	else
	{
		input[*x] = ' ';
		token_to_dllist(shell, *x, *x + 1, '\0');
		(*x)++;
	}
}
