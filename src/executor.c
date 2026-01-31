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
