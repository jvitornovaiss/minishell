/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 21:26:36 by rida-cos          #+#    #+#             */
/*   Updated: 2026/02/01 22:40:53 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **fill_args(t_token **tokens, t_cmd *new_node)
{
	int		n_args;
	char	**args;
	int		i;

	n_args = count_args(*tokens);
	args = malloc(sizeof(char *) * (n_args + 1));
	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if (is_redirect((*tokens)->type))
		{
			handle_redirections(new_node, tokens);
		}
		else
		{
			args[i] = ft_strdup((*tokens)->value);
			i++;
			*tokens = (*tokens)->next;
		}
	}
	args[i] = NULL;
	return (args);
}

t_cmd *build_commands(t_token *tokens)
{
	t_cmd *head;
	t_cmd *new_node;
	t_token *curr;
	
	process_all_heredocs(tokens);
	head = NULL;
	curr = tokens;
	while (curr)
	{
		new_node = create_cmd_node();
		new_node->args = fill_args(&curr, new_node);
		add_cmd(new_node, &head);
		if (curr && curr->type == PIPE)
			curr = curr->next;
	}
	return(head);
}


// // No seu loop principal de parsing
// int pipe_rd = 0; // Começa em 0 (stdin padrão)

// while (tokens)
// {
//     t_cmd *node = create_new_node();
    
//     // 1. O nó herda a ponta de leitura do comando anterior (se houver)
//     node->fd_in = pipe_rd;
//     pipe_rd = 0; // Reseta para não dar o mesmo FD para todo mundo

//     // 2. Preenche o comando (args, redirecionamentos manuais)
//     fill_node_data(node, &tokens);

//     // 3. Se o token atual for um PIPE
//     if (tokens && tokens->type == PIPE)
//     {
//         int fd[2];
//         pipe(fd);
        
//         // Se o comando atual NÃO tem redirecionamento manual (>), usa o pipe
//         if (node->fd_out == 1)
//             node->fd_out = fd[1];
//         else
//             close(fd[1]); // Fecha se o usuário usou "> arquivo"

//         // GUARDA a ponta de leitura para o PRÓXIMO comando usar
//         pipe_rd = fd[0];
        
//         tokens = tokens->next; // Pula o '|'
//     }
//     add_back_cmd(&cmd_list, node);
// }