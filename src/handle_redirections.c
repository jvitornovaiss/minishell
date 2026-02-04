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
	{
		perror((*tokens)->value);
		node->invalid = 1;
		g_exit_status = 1;
	}
}

void open_input_file(t_cmd *node, t_token **tokens)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = open((*tokens)->value, O_RDONLY);
	if (node->fd_in == -1)
	{
		perror((*tokens)->value);
		node->invalid = 1;
		g_exit_status = 1;
	}
}

void handle_redirections(t_cmd *node, t_token **tokens)
{
	t_token_type type;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!(*tokens) || ((*tokens)->type != WORD))
	{
		syntax_error_message((*tokens)->value);
		node->invalid = 1; //invalid
		g_exit_status = 2;
		return ;
	}
	if (type == RED_OUT || type == APPEND)
		open_output_file(type, node, tokens);
	else if (type == RED_IN)
		open_input_file(node, tokens);
	*tokens = (*tokens)->next;
}