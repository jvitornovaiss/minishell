#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *s;
    s = readline("Prompt > ");
    printf("%s\n", s);
    free(s);
    return (0);
}