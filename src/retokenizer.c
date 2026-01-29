/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:49:41 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/29 00:08:17 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    split_and_relink(t_token *token)
{
    
}


void retokenizer(t_token **tokens)
{
    t_token *curr;

    if (!tokens || !*tokens)
        return ;
    curr = *tokens;
    while (curr)
    {
        if (curr->type == WORD && strchr(curr->value, 1))
            split_and_relink(curr);
        curr = curr->next;
    }
}