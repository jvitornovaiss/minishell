/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:06:57 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/24 23:34:51 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token *node;
	
	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = value;
	node->type = type;
	node->next = NULL;
	return (node);
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void free_tokens(t_token *head)
{
	t_token *temp;

	while (head)
	{
		temp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = temp;
	}
}

char *clean_quotes(char *str)
{
    char    *new;
    int     i;
    int     j;
    t_state state;

    new = malloc(sizeof(char) * (ft_strlen(str) + 1));
    i = 0;
    j = 0;
    state = OUT_QUOTE;
    while (str[i])
    {
        if (state == OUT_QUOTE && str[i] == '\'')
            state = IN_SQUOTE;
        else if (state == OUT_QUOTE && str[i] == '\"')
            state = IN_DQUOTE;
        else if (state == IN_SQUOTE && str[i] == '\'')
            state = OUT_QUOTE;
        else if (state == IN_DQUOTE && str[i] == '\"')
            state = OUT_QUOTE;
        else
            new[j++] = str[i]; // Só copia se não for a aspa de controle
        i++;
    }
    new[j] = '\0';
    return (new);
}