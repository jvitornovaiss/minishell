/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:39:58 by rida-cos          #+#    #+#             */
/*   Updated: 2026/02/01 22:55:50 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc_lines(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter,
				ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

static void	handle_heredoc(t_cmd *node, char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		node->fd_in = -1;
		return ;
	}
	read_heredoc_lines(pipefd[1], delimiter);
	close(pipefd[1]);
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	node->fd_in = pipefd[0];
}

static void	handle_output(t_cmd *node, char *filename, t_token_type type)
{
	int	flags;

	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	if (type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	node->fd_out = open(filename, flags, 0644);
	if (node->fd_out == -1)
		perror(filename);
}

void	handle_redirections(t_cmd *node, t_token **tokens)
{
	t_token_type	type;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!(*tokens))
		return ;
	if (type == RED_OUT || type == APPEND)
		handle_output(node, (*tokens)->value, type);
	else if (type == RED_IN)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		node->fd_in = open((*tokens)->value, O_RDONLY);
		if (node->fd_in == -1)
			perror((*tokens)->value);
	}
	else if (type == HERE_DOC)
		handle_heredoc(node, (*tokens)->value);
	*tokens = (*tokens)->next;
}
