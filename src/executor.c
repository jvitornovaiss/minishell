/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:38:02 by jnovais           #+#    #+#             */
/*   Updated: 2026/01/23 23:38:02 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_cmd	*tokens_to_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	int		count;
	int		i;

	count = count_word_tokens(tokens);
	if (count == 0)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *) * (count + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			cmd->argv[i] = ft_strdup(tokens->value);
			i++;
		}
		tokens = tokens->next;
	}
	cmd->argv[i] = NULL;
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	free(cmd);
}

static void	print_error(char *prefix, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (prefix)
	{
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

int	execute_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = find_cmd_path(cmd->argv[0], envp);
	if (!path)
	{
		print_error(cmd->argv[0], "command not found");
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		print_error("fork", "failed to create process");
		free(path);
		return (1);
	}
	if (pid == 0)
	{
		execve(path, cmd->argv, envp);
		print_error("execve", "execution failed");
		free(path);
		_exit(127);
	}
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
