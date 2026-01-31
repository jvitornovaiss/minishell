/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:53:16 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/30 00:37:52 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_setup env;
	t_token	*temp;

	(void)argc;
	(void)argv;
	env.envp = envp;
	while (1)
	{
		input = readline("minishell > ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		tokens = lexer(input);
		expander(tokens, env);
		retokenizer(&tokens);
		remove_quotes(tokens);
		printf("\n---APÓS REMOVER QUOTES---\n");
		temp = tokens;
		while (temp)
		{
			printf("Value: %s\tType: %d\n", temp->value, temp->type);
			temp = temp->next;
		}
		build_commands();
		free_tokens(tokens);
		free(input);
	}
	return (0);
}


// TO DO
// 1. implementar remove_quotes
// 2. 
// 3. Estudar os diferentes comportamentos para diferentes tipos de declaracao da variavel
// 4. 
//
//
//
//
//
