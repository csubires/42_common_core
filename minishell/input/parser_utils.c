/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:17:39 by csubires          #+#    #+#             */
/*   Updated: 2024/11/30 10:37:04 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_heredoc(char *delimiter)
{
	char	*join_str;
	char	*tmp_join;
	char	*read_str;

	join_str = 0;
	while (1)
	{
		read_str = readline(" heredoc> ");
		if (!read_str || !ft_strcmp(read_str, delimiter))
			break ;
		if (!join_str)
			tmp_join = ft_strdup(read_str);
		else
			tmp_join = ft_strconcat(3, join_str, "\n", read_str);
		free(read_str);
		free(join_str);
		join_str = tmp_join;
	}
	tmp_join = ft_strconcat(2, join_str, "\n");
	if (read_str)
		free(read_str);
	free(join_str);
	return (tmp_join);
}

static void	manage_input(t_exec *exec_cmd, t_dllist **token_ptr)
{
	if ((*token_ptr)->next)
	{
		if (!ft_strcmp((char *)(*token_ptr)->data, "<"))
		{
			if (exec_cmd->heredoc_delimiter)
				dlist_free((void **)&(exec_cmd->heredoc_delimiter));
			*token_ptr = (*token_ptr)->next;
			exec_cmd->input_file = ft_strdup((char *)(*token_ptr)->data);
			if (!file_exists(exec_cmd->input_file))
				ft_fdprint(exec_cmd->out_fd, "%s: %s\n" \
				, exec_cmd->input_file, ERR_PATH);
		}
		else if (!ft_strcmp((char *)(*token_ptr)->data, "<<"))
		{
			if (exec_cmd->input_file)
				dlist_free((void **)&(exec_cmd->input_file));
			*token_ptr = (*token_ptr)->next;
			exec_cmd->heredoc_delimiter = ft_strdup((char *)(*token_ptr)->data);
			if (exec_cmd->heredoc_delimiter[0] == '<')
				return ((void)print_error(1, 0, ERR_TOKEN, "<"));
			exec_cmd->heredoc_data = read_heredoc(exec_cmd->heredoc_delimiter);
		}
	}
}

static void	manage_output(t_exec *exec_cmd, t_dllist *token_ptr[])
{
	if (exec_cmd->output_file)
		dlist_free((void **)&(exec_cmd->output_file));
	if (!ft_strcmp((char *)(*token_ptr)->data, ">>"))
		exec_cmd->append_to_fd = 1;
	*token_ptr = (*token_ptr)->next;
	exec_cmd->output_file = ft_strdup((char *)(*token_ptr)->data);
	manage_output_fd(exec_cmd, 0);
}

void	manage_redirection(t_exec *exec_cmd, t_dllist *token_ptr[])
{
	char	*token_data;

	if (!(*token_ptr)->next)
		return ;
	token_data = (char *)(*token_ptr)->data;
	if (!ft_strcmp((char *)(*token_ptr)->data, "<") || \
		!ft_strcmp(token_data, "<<"))
		manage_input(exec_cmd, token_ptr);
	else if (!ft_strcmp((char *)(*token_ptr)->data, ">") || \
		!ft_strcmp((char *)(*token_ptr)->data, ">>"))
		manage_output(exec_cmd, token_ptr);
}
