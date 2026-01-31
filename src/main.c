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

static void	run_command(t_token *tokens, char **envp)
{
	t_cmd	*cmd;

	cmd = tokens_to_cmd(tokens);
	if (cmd)
	{
		execute_cmd(cmd, envp);
		free_cmd(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_setup	env;

	(void)argc;
	(void)argv;
	env.envp = envp;
	while (1)
	{
		input = readline("minishell > ");
		if (!input)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		tokens = lexer(input);
		expander(tokens, env);
		retokenizer(&tokens);
		run_command(tokens, envp);
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
