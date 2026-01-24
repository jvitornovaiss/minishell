/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 22:51:36 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/21 21:33:26 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
    pid_t pid;

    pid = fork(); // Cria o clone
    if (pid == 0) // Estamos no processo FILHO
    {
        char *args[] = {"/bin/ls", "-l", NULL};
        execve(args[0], args, NULL); // O filho "vira" o comando ls
    }
    else // Estamos no processo PAI
    {
        wait(NULL); // Espera o filho terminar
        printf("O comando terminou! Pronto para o próximo.\n");
    }
    return (0);
}

//20    |
//21    |
//22    |   |
//23    |   |
//25        X
//29    |
//30    |
//
//
