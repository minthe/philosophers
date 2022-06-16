/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:02:19 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/06/16 13:13:58 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->data->nbr_philo);
	if (thread == NULL)
		return (1);
	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_create(&thread[i], NULL, philo_cycle, philo + i);
		philo[i].thread = thread[i];
		philo[i].last_meal = time_current();
		if (i % 2 == 0)
			usleep(10);
		i++;
	}
	return (0);
}

int	manage_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_mutex_destroy(&philo->mutex[i]);
		i++;
		// free (philo[i].thread);
		// free (philo[i].fork);
	}
	pthread_mutex_destroy(&philo->data->status);
	if (philo)
		free(philo);
	return (0);
}
