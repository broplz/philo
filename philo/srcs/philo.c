#include "../includes/philo.h"

int	ft_atoi(char *str) // TODO защитить атой
{
	int res;

	res = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return res;
}

void	init_philo(t_philo *philo, int name, unsigned left, unsigned right)
{
	philo->name = name;
	philo->left_fork = left;
	philo->right_fork = right;
}

void* eat(void *args)
{
	t_philo *philo = (t_philo *)args;
	while (philo->var->dead == 0)
	{
		PML(&philo->var->forks[philo->left_fork]);
		PML(&philo->var->print);
		printf("timestamp_in_ms %d has taken a left fork", philo->name);
		PMU(&philo->var->print);

		PML(&philo->var->forks[philo->right_fork]);
		PML(&philo->var->print);
		printf("timestamp_in_ms %d has taken a right fork", philo->name);
		printf("%d is eating\n", philo->name + 1);
		PMU(&philo->var->print);
		usleep(philo->var->eat_time * 1000);

		PMU(&philo->var->forks[philo->left_fork]);
		PMU(&philo->var->forks[philo->right_fork]);
		PML(&philo->var->print);
		printf("timestamp_in_ms %d is sleeping", philo->name);
		PMU(&philo->var->print);
		usleep(philo->var->sleep_time * 1000);

		PML(&philo->var->print);
		printf("timestamp_in_ms %d is thinking", philo->name);
		PMU(&philo->var->print);
	}
}

ULL	current_time()
{

}

void init_vars(t_var *var, char **av)
{
	var->dead = 0;
	var->full = 0;
	var->p_amount = ft_atoi(av[1]);
	var->think_time = ft_atoi(av[2]);
	var->eat_time = ft_atoi(av[3]);
	var->sleep_time = ft_atoi(av[4]);
	if (var->p_amount == 6)
		var->number_of_meals = ft_atoi(av[5]);
	var->forks = (PMT *)malloc(sizeof(PMT) * var->p_amount);
	var->philo = (t_philo *)malloc(sizeof(t_philo));
	int i = 0;
	while (i < var->p_amount)
	{
		pthread_mutex_init(&var->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&var->print, NULL);
}

void	create_tread(t_var *var)
{
	int i;

	i = 0;
	while (i < var->p_amount)
	{
		pthread_create(&var->philo->thread, NULL, eat, &var->philo[i]);
		i++;
		usleep(50);
	}

}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_var		var;
	int			i;

	init_vars(&var, av);
	i = 0;
	while (i < var.p_amount - 1)
	{
		init_philo(&var.philo[i], i, i, i + 1);
		i++;
	}
	init_philo(&var.philo[i], i, i, 0);
	create_tread(&var);

	return (0);
}