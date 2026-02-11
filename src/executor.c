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

static void	apply_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	close_cmd_fds(t_cmd *cmd)
{
	if (cmd->fd_in > STDERR_FILENO)
	{
		close(cmd->fd_in);
		cmd->fd_in = STDIN_FILENO;
	}
	if (cmd->fd_out > STDERR_FILENO)
	{
		close(cmd->fd_out);
		cmd->fd_out = STDOUT_FILENO;
	}
}

int	execute_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		return (1);
	path = find_cmd_path(cmd->args[0], envp);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		close_cmd_fds(cmd);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		close_cmd_fds(cmd);
		return (1);
	}
	if (pid == 0)
	{
		apply_redirections(cmd);
		execve(path, cmd->args, envp);
		perror("execve");
		free(path);
		exit(127);
	}
	free(path);
	close_cmd_fds(cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
