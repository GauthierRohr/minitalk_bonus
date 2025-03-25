/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:17:16 by grohr             #+#    #+#             */
/*   Updated: 2025/03/25 18:08:29 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

// Fonction de gestion des signaux
//bit : Compteur de bits reçus (persistant entre les appels)
//c_created : Caractère en cours de construction (persistant entre les appels)
//c_created |= (0x01 << bit) : si SIGUSR1 reçu, on met le bit correspondant à 1
//(bit == 8) : Si on a reçu 8 bits (un caractère complet)
void	ft_handler(int signal)
{
	static int	bit;
	static int	c_created;

	if (signal == SIGUSR1)
		c_created |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", c_created);
		bit = 0;
		c_created = 0;
	}
}

//(void)argv : Pour éviter un warning de variable non utilisée
//while (argc == 1)	: Boucle infinie tant que le programme n'est pas interrompu
//pause() : On met le processus en pause jusqu'à réception d'un signal
int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./server\033[0m\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	while (argc == 1)
	{
		signal(SIGUSR1, ft_handler);
		signal(SIGUSR2, ft_handler);
		pause();
	}
	return (0);
}
