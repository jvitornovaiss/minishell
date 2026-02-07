/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:39:58 by rida-cos          #+#    #+#             */
/*   Updated: 2026/02/03 23:24:22 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void open_output_file(t_token_type type, t_cmd *node, t_token **tokens)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	if (type == RED_OUT)
		node->fd_out = open((*tokens)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		node->fd_out = open((*tokens)->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->fd_out == -1)
		set_error((*tokens)->value, node, 1);
}

void open_input_file(t_cmd *node, t_token **tokens)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = open((*tokens)->value, O_RDONLY);
	if (node->fd_in == -1)
		set_error((*tokens)->value, node, 1);
}

void read_heredoc(int fd_read, int fd_write, char *delimiter)
{
	char *line;

	close(fd_read);
		while (1)
		{
			line = readline("> ");
			if (!line || (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0))
			{
				if (!line)
					ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 2);
				free(line);
				break ;
			}
			ft_putendl_fd(line, fd_write);
			free(line);
		}
		close(fd_write);
		exit(0);
}

void	handle_heredoc(t_cmd *node, char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (set_error("minishell: pipe", node, 1));
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
        return (set_error("minishell: fork", node, 1));
	}
	if (pid == 0)
		read_heredoc(fd[0], fd[1], delimiter);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status =	WEXITSTATUS(status);
	if (node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = fd[0];
}

void handle_redirections(t_cmd *node, t_token **tokens)
{
	t_token_type type;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!(*tokens) || ((*tokens)->type != WORD))
	{
		if ((*tokens)->value)
			syntax_error_message("newline");
		else
			syntax_error_message((*tokens)->value);
		node->invalid = 1;
		g_exit_status = 2;
		return ;
	}
	if (node->invalid)
        return ;
	if (type == RED_OUT || type == APPEND)
		open_output_file(type, node, tokens);
	else if (type == RED_IN)
		open_input_file(node, tokens);
	else if (type == HERE_DOC)
		handle_heredoc(node, (*tokens)->value);
	*tokens = (*tokens)->next;
}