/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:28:36 by grohr             #+#    #+#             */
/*   Updated: 2025/03/25 18:10:38 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk_bonus.h"

void	ft_handler(int signal, siginfo_t *info, void *s)
{
	static int		bit;
	static int		c;
	static pid_t	client_pid;

	client_pid = 0;
	(void)s;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (info->si_pid != client_pid)
		return ;
	if (signal == SIGUSR1)
		c |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		if (c == '\n')
		{
			usleep(100);
			kill(client_pid, SIGUSR1);
			client_pid = 0;
		}
		c = 0;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

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
	sig.sa_sigaction = ft_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}
