/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:08:41 by grohr             #+#    #+#             */
/*   Updated: 2025/03/25 18:09:08 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk_bonus.h"

static void	ft_confirm(int signal)
{
	(void)signal;
	ft_printf("\033[1;32mMessage reçu ✔️\033[0m\n");
	exit(0);
}

void	ft_send_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		signal(SIGUSR1, ft_confirm);
		while (argv[2][i] != '\0')
			ft_send_bits(pid, argv[2][i++]);
		ft_send_bits(pid, '\n');
		while (1)
			pause();
	}
	else
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./client_bonus [PID] [MESSAGE]\033[0m\n");
		return (1);
	}
	return (0);
}
