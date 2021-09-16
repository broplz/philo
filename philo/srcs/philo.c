#include "../includes/philo.h"

void	init_args(t_table *table)
{
	table->args.eat = 100;
	table->args.sleep = 100;
	table->args.think = 200;
	table->args.philos = 7;
	table->size = 0;
}

void	init_philo(t_philo *philo, int num)
{
	philo->name = num;
}

int	create_philo(t_table *table)
{
	while (table->size < table->args.philos)
	{
		t_philo *philo;

		philo = (t_philo *)malloc(sizeof(t_philo));
		if (philo == NULL)
			return (1);
		init_philo(philo, table->size);
		if (table->size == 0)
		{
			philo->next = philo;
			philo->prev = philo;
			table->head = *philo;
			free(philo);
		}
		else
		{
			philo->next = &table->head;
			philo->prev = table->head.prev;
			table->head.prev->next = philo;
			table->head.prev = philo;
		}

		table->size++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = (t_table *) malloc(sizeof(t_table));
	if (table == NULL)
		return (1);
	table->size = 5;
	init_args(table);
	create_philo(table);


	t_philo *curr = &table->head;
	// DEBUG INFO
	for (int i = 0; i < table->size; ++i) {
		printf("%d - philo name\n", curr->name);
		curr = curr->next;
	}

//	printf("%d - args sleep\n", table->args.sleep);
//	printf("%d - args think\n", table->args.think);
//	printf("%d - args eat\n", table->args.eat);
//	printf("%lu - allocated memory to table\n", sizeof(table));
//	printf("%d - table size\n", table->size);
}
