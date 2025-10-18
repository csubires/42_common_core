/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:05:48 by csubires          #+#    #+#             */
/*   Updated: 2024/11/16 11:28:18 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cd_change(t_shell *shell, char *old_pwd, \
char *new_pwd, char *path)
{
	printf("\ndebug OLD %s]", old_pwd);
	printf("\ndebug NEW %s]", new_pwd);
	printf("\ndebug PWD %s]", get_env_value(shell->env_list, "PWD"));
	printf("\ndebug OLD %s]", get_env_value(shell->env_list, "OLDPWD"));
	printf("\nTO PATH %s", path);
}

void	print_path(char **array_paths)
{
	int			x;

	if (!array_paths)
		return ;
	x = 0;
	printf("\nENV PATH ARRAY FOR EXECUTABLES BIN:\n");
	while (array_paths[x])
	{
		printf("[%d] %s\n", x, array_paths[x]);
		x++;
	}
}

void	print_token_list(t_shell *shell)
{
	t_dllist	*tmp_list;
	int			x;

	x = 0;
	tmp_list = shell->token_list;
	printf("\nTOKEN LIST:\n");
	while (tmp_list)
	{
		printf("[%d] %s\n", ++x, (char *)tmp_list->data);
		tmp_list = tmp_list->next;
	}
}

static void	print_exec_args_list(t_exec *data)
{
	t_dllist	*tmp_list;
	int			x;

	x = 0;
	tmp_list = data->arg_list;
	printf("\nARGUMENT LIST(%d):", (int)dlist_size(tmp_list));
	while (tmp_list)
	{
		printf("\n%d:[%s%s%s]", ++x, YELLOW, (char *)tmp_list->data, ENDC);
		tmp_list = tmp_list->next;
	}
}

void	print_exec_list(t_shell *shell)
{
	t_dllist	*tmp_list;
	t_exec		*data;

	tmp_list = shell->exec_list;
	printf("\nCOMMAND LIST (%d):", shell->num_of_cmds);
	while (tmp_list)
	{
		data = (t_exec *)tmp_list->data;
		printf("\nCommand: %s %s %s\n", RED, data->executable, ENDC);
		print_exec_args_list(data);
		printf("\n\n%sINPUT: File[%s] FD(%d) | OUTPUT: File[%s] FD(%d) %s\n", \
		YELLOW, data->input_file, data->in_fd, \
		data->output_file, data->out_fd, ENDC);
		printf("%sAppend: %d, Heredoc: dlt[%s], data[%s] %s\n", YELLOW, \
		data->append_to_fd, data->heredoc_delimiter, data->heredoc_data, ENDC);
		tmp_list = tmp_list->next;
	}
	printf("\n");
}
