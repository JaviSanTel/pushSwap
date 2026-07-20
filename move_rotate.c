
void	rotate(t_list	*stack)
{
	t_list	*aux;
	int	temp;

	while (stack != NULL || stack->next != NULL)
	{
		aux = stack;
		temp = aux->content;
		while (aux->next)
		{
			aux = aux->next;
		}
		stack->content = aux->content;
		aux->content = temp;
	}
}

int	rotate_a(t_list *stack)
{
	

}
