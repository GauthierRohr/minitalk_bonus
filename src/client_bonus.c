/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:22:49 by grohr             #+#    #+#             */
/*   Updated: 2025/03/26 21:02:00 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk_bonus.h"

void	send_signal(int pid, char *str)
{
	int		i;
	int		c;
	char	*final;

	final = str + ft_strlen(str);
	while (str <= final)
	{
		c = *str;
		i = 0;
		while (i < 8)
		{
			if (c & (1 << i))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(200);
			i++;
		}
		str++;
	}
}

void	server_signal(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("\033[1;32mMessage received successfully ✔️\033[0m\n");
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_handler = &server_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
	{
		ft_printf("\033[38;5;196mError: wrong format.\033[0m\n");
		ft_printf("\033[33mFormat: ./client_bonus <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("\033[38;5;196mError: Invalid PID.\033[0m\n");
		return (1);
	}
	else
		send_signal(pid, argv[2]);
	return (0);
}
