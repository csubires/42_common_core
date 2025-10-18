/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesumore <jesumore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:39:58 by csubires          #+#    #+#             */
/*   Updated: 2024/11/30 13:23:08 by jesumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_token(t_shell *shell, char *input, int *x)
{
	int		start;
	int		end;
	char	quote;
	char	before_quote;

	if (input[*x] && (input[*x] == '\'' || input[*x] == '\"'))
	{
		if (*x == 0)
			return (1);
		else
			before_quote = input[*x - 1];
		quote = input[*x];
		start = ++(*x);
		while (input[*x] && input[*x] != quote)
			(*x)++;
		end = *x;
		token_to_dllist(shell, start, end, before_quote);
		(*x)++;
	}
	return (0);
}

int	split_tokens(t_shell *shell, char *input)
{
	int		x;

	if (!*input)
		return (2);
	x = 0;
	while (x < (int)ft_strlen(input))
	{
		if (check_token(shell, input, &x) == 1)
			return (1);
		if (x >= (int)ft_strlen(input))
			return (2);
		set_redirect(shell, input, &x);
		if (x >= (int)ft_strlen(input))
			return (2);
		if (!ft_isprint(input[x]) || ft_isspace(input[x]))
			x++;
		else
			tokenise_arg(shell, input, &x);
	}
	return (0);
}

static void	manage_quotes(char c, int *flag)
{
	if (!*flag)
	{
		if (c == '\'')
			*flag = 1;
		else if (c == '\"')
			*flag = 2;
	}
	else if (*flag == 1 && c == '\'')
		*flag = 3;
	else if (*flag == 2 && c == '\"')
		*flag = 4;
}

void	replace_with_envp(t_shell *shell)
{
	int		flag;
	int		x;

	flag = 0;
	if (check_double_quote(shell))
		return ((void)print_error(1, shell, ERR_QUOT, 0));
	x = 0;
	while (shell->input[x])
	{
		if (flag == 3)
			flag = 0;
		manage_quotes(shell->input[x], &flag);
		if ((flag == 0 || flag == 2 || flag == 4) && shell->input[x] == '$')
		{
			expand_envp(shell, &x);
			flag = 0;
		}
		else
			x++;
	}
}

void	tokens_to_dllist(t_shell *shell)
{
	char	*first_token;
	char	*last_token;

	if (token_to_dllist_check(shell) != 0)
		return ;
	first_token = (char *)shell->token_list->data;
	if (first_token && (first_token[0] != '\"') && \
	(first_token[0] != '\'') && !isnt_metachar(first_token[0]))
	{
		print_error(1, shell, ERR_TOKEN, 0);
		return ;
	}
	last_token = (char *)(dlist_last(shell->token_list)->data);
	if (!ft_strcmp(last_token, "|"))
	{
		print_error(1, shell, ERR_TOKEN, 0);
		return ;
	}
}
