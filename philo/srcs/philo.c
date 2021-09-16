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
//
//void eat(t_table *var)
//{
//	t_args *arg = var->var;
//	t_philo *philo
//}

void	init_philo(t_philo *philo, int name, unsigned left, unsigned right)
{
	philo->name = name;
	philo->left_fork = left;
	philo->right_fork = right;
}

void init_table(t_table *table)
{
	size_t i;

	i = 0;
	while (i < table->forks_amount)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void eat(void *args)
{
	t_args *arg = (t_args *)args;
	t_philo *philo = arg->philo;
	t_table *table = arg->table;

	printf("%d started to eat\n", philo->name);

	pthread_mutex_lock(&table->forks[philo->left_fork]);
	pthread_mutex_lock(&table->forks[philo->right_fork]);

	printf("%d is eating\n", philo->name);

	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);

	printf("%d finished to eat\n", philo->name);
}
int	main(int ass, char **dicks)
{
	pthread_t	threads[ft_atoi(dicks[1])];
	t_philo		philo[ft_atoi(dicks[1])];
	t_table		table;
	size_t		i;

//	table = (t_table *)malloc(sizeof(t_table));
	table.forks_amount = ft_atoi(dicks[1]);
	init_table(&table);
//	t_args *args;
//
//	args = (t_args *)malloc(sizeof(t_args));
//	if (args == NULL)
//		return (1);
//	args->table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(dicks[1]));
//	if (args->table->forks == NULL)
//		return (1);
//	if (ass < 5 || ass > 6)
//		return (2);
//	args->var->philo_amount = ft_atoi(dicks[1]);
//	args->var->think_time = ft_atoi(dicks[2]);
//	args->var->eat_time = ft_atoi(dicks[3]);
//	args->var->sleep_time = ft_atoi(dicks[4]);
//	if (ass == 6)
//		args->var->number_of_meals = ft_atoi(dicks[5]);
//	init_table(args);


	//DEBUG
//	printf("%d - var->var->philo_amount\n", args->var->philo_amount);
//	printf("%d - var->var->think_time\n", args->var->think_time);
//	printf("%d - var->var->eat_time\n", args->var->eat_time);
//	printf("%d - var->var->sleep_time\n", args->var->sleep_time);
//	printf("%d - var->var->number_of_meals\n", args->var->number_of_meals);
	printf("%ld - allocated memory size\n", sizeof(t_table));
	return (0);
}