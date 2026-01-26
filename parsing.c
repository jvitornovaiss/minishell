/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:53:16 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/25 23:27:37 by rida-cos         ###   ########.fr       */
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
		tokens = lexer(input);
		if (strcmp(input, "exit") == 0)
		{
			free_tokens(tokens);
			free(input);
			break ;
		}
		temp = tokens;
		printf("\n---ANTES DE EXPANDIR---\n");
		while (temp)
		{
			printf("Value: %s\tType: %d\n", temp->value, temp->type);
			temp = temp->next;
		}
		temp = tokens;
		expander(temp, env);
		temp = tokens;
		printf("\n---APÓS EXPANDIR---\n");
		while (temp)
		{
			printf("Value: %s\tType: %d\n", temp->value, temp->type);
			temp = temp->next;
		}
		free_tokens(tokens);
		free(input);
	}
	return (0);
}


// TO DO
// 1. Com a prepare_to_split pronta, fazer a rotina para retokenizar
// 2. 
// 3. 
//
//
//
//
//
//
