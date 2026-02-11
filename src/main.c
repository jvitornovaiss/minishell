/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:53:16 by rida-cos          #+#    #+#             */
/*   Updated: 2026/02/11 01:07:59 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

static void print_commands(t_cmd *head)
{
    int i;
    int cmd_count = 0;

    while (head)
    {
        printf("\n--- COMANDO %d ---\n", ++cmd_count);
        printf("FD IN: %d\n", head->fd_in);
        printf("FD OUT: %d\n", head->fd_out);
		printf("INVALID: %d\n", head->invalid);
        i = 0;
        while (head->args && head->args[i])
        {
            printf("Arg[%d]: %s\n", i, head->args[i]);
            i++;
        }
        head = head->next;
    }
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_token	*tokens;
// 	t_setup	env;
// 	//t_token	*temp;
// 	t_cmd	*cmds;

// 	(void)argc;
// 	(void)argv;
// 	env.envp = copy_environment(envp);
// 	while (1)
// 	{
// 		input = readline("minishell > ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (strcmp(input, "exit") == 0)
// 		{
// 			free(input);
// 			break ;
// 		}
// 		tokens = lexer(input);
// 		expander(tokens, env);
// 		retokenizer(&tokens);
// 		remove_quotes(tokens);
// 		cmds = build_commands(tokens);
// 		print_commands(cmds);
// 		free_tokens(tokens);
// 		free_commands(cmds);
// 		free(input);
// 	}
// 	return (0);
// }


int main(int argc, char **argv, char **envp)
{
    t_setup setup;
    int     i;

    setup.envp = copy_environment(envp); // Sua função

    // 1. Teste de Endereços (Deep Copy Check)
    printf("--- TESTE DE MEMÓRIA ---\n");
    printf("Endereço do array original: %p\n", (void *)envp);
    printf("Endereço da sua cópia:      %p\n", (void *)setup.envp);
    
    if (envp[0] && setup.envp[0])
    {
        printf("Endereço da 1ª string original: %p (%s)\n", (void *)envp[0], envp[0]);
        printf("Endereço da 1ª string cópia:    %p (%s)\n", (void *)setup.envp[0], setup.envp[0]);
    }

    // 2. Teste de Independência
    printf("\n--- TESTE DE INDEPENDÊNCIA ---\n");
    // Vamos alterar APENAS a nossa cópia
    free(setup.envp[0]);
    setup.envp[0] = ft_strdup("VAR_TESTE=MODIFICADO");

    printf("Original envp[0]: %s\n", envp[0]);
    printf("Cópia setup.envp[0]: %s\n", setup.envp[0]);

    // Limpeza para evitar leaks no teste
    // free_env(setup.envp, size); 
    return (0);
}

// TO DO
// 1. Checar leak de FD abertos
// 2. Estudar mais sobre redirections.
// 3. Realizar mais testes individuais sobre redirections
// 4. 
//
//
//
//
//
