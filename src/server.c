/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:28:03 by grohr             #+#    #+#             */
/*   Updated: 2025/03/26 21:06:39 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

char	*g_msg = NULL;

// Calculer la longueur actuelle du message
// Allouer un nouveau buffer (+2 pour le nouveau char et le '\0')
// Copier l'ancien message si existant
// Ajouter le nouveau caractère
// Mettre à jour le pointeur global
void	add_char(char c)
{
	char	*new;
	size_t	len;

	if (g_msg)
		len = ft_strlen(g_msg);
	else
		len = 0;
	new = malloc(len + 2);
	if (!new)
		exit(1);
	if (g_msg)
	{
		ft_memcpy(new, g_msg, len);
		free(g_msg);
	}
	new[len] = c;
	new[len + 1] = '\0';
	g_msg = new;
}

// Signal handler function
void	handler(int signal, siginfo_t *sig_info, void *context)
{
	static int	bit_index = 0;
	static char	c = 0;

	(void)context;
	(void)sig_info;
	if (signal == SIGUSR2)
		c |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (c == '\0')
		{
			ft_printf("%s\n", g_msg);
			free(g_msg);
			g_msg = NULL;
		}
		else
			add_char(c);
		bit_index = 0;
		c = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 1)
	{
		ft_printf("\033[38;5;196mError: wrong format.\033[0m\n");
		return (ft_printf("\033[33mUsage: %s\033[0m\n", argv[0]), 0);
	}
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("\033[94mPID -> \033[0m%d\n", getpid());
	ft_printf("\033[90mWaiting...\033[0m\n");
	while (1)
		pause();
	return (0);
}
