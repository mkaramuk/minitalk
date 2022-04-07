/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaramuk <mkaramuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:00:56 by mkaramuk          #+#    #+#             */
/*   Updated: 2022/02/08 18:07:33 by mkaramuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	print_pid(void)
{
	ft_printf("Process ID: %d\n", getpid());
}

void	take_bit(int signo, siginfo_t *info, void *p)
{
	static int	g_bit_count = 0;
	static int	g_number = 0;

	(void)p;
	g_number <<= 1;
	if (signo == SIGUSR1)
		g_number |= 1;
	g_bit_count++;
	if (g_bit_count == 8)
	{
		write(1, &g_number, 1);
		if (g_number == 0)
		{
			send_signal(SIGUSR1, info->si_pid);
			ft_printf("\nThis data recieved from %d\n", info->si_pid);
		}
		g_number = 0;
		g_bit_count = 0;
		send_signal(SIGUSR2, info->si_pid);
	}
}

int	main(void)
{	
	struct sigaction	sa;

	print_pid();
	sa.sa_sigaction = take_bit;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset (&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == 1)
		error("Signal couldn't set");
	if (sigaction(SIGUSR2, &sa, NULL))
		error("Signal couldn't set");
	while (1)
		continue ;
	return (0);
}
