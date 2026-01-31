
#include "minishell.h"

t_cmd *create_cmd_node()
{
    t_cmd *node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->fd_in = 0;
    node->fd_out = 1;
    node->next = NULL;

    return (node);
}

t_cmd *build_commands(t_token *tokens)
{
    t_cmd *head;
    t_cmd *new_node;
    t_token *curr;

    head = NULL;
    curr = tokens;
    while (curr)
    {
        new_node = create_cmd_node();
        //logica
        curr = curr->next;
    }
    return(head);
}