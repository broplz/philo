#include "../includes/philo.h"

int	ft_atoi(char *str)
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

void init_table(t_args *args)
{
	size_t i;

	i = 0;
	while (i < args->var.p_amount)
	{
		pthread_mutex_init(&args->table->forks[i], NULL);
		i++;
	}
}

void eat(void *args)
{
	t_args *arg = (t_args *)args;
	t_philo *philo = arg->philo;
	t_table *table = arg->table;

	printf("%d started to eat\n", philo->name);

	PML(&table->forks[philo->left_fork]);
	PML(&table->forks[philo->right_fork]);

	printf("%d is eating\n", philo->name);

	PMU(&table->forks[philo->left_fork]);
	PMU(&table->forks[philo->right_fork]);

	printf("%d finished to eat\n", philo->name);
}

void	malloc_all(t_args *args)
{
	args->table = (t_table *)malloc(sizeof(t_table));
	args->table->forks = (PMT *)malloc(sizeof(PMT) * args->var.p_amount);
	args->philo = (t_philo *)malloc(sizeof(t_philo) * args->var.p_amount);
}

void init_vars(t_args *args, char **av)
{
	args->var.p_amount = ft_atoi(av[1]);
	args->var.think_time = ft_atoi(av[2]);
	args->var.eat_time = ft_atoi(av[3]);
	args->var.sleep_time = ft_atoi(av[4]);
	args->var.number_of_meals = ft_atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_args		args;
	int			i;

	i = 0;
	init_vars(&args, av);
	malloc_all(&args);
	init_table(&args);
	while (i < args.var.p_amount - 1)
	{
		init_philo(&args.philo[i], i, i, i + 1);
		i++;
	}
	init_philo(&args.philo[i], i, i, 0);

	i = 0;
	while (i < args.var.p_amount)
	{
		printf("%d - id of philo, %d - left, %d - right\n", args.philo[i].name, args.philo[i].left_fork, args.philo[i].right_fork);
		i++;
	}
	return (0);
}