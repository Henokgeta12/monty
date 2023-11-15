/**
 * push - this function pushes an integer onto the stack
 * @stack: double pointer to the stack.
 * @line_number: line number.
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *token;
	int value;

	token = strtok(NULL, " \t\n");
	if (token == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	if (sscanf(token, "%d", &value) != 1)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	push_node(stack, value);
}

/**
 * push_node - this function pushes a new node with the given value onto the stack
 * @stack: double pointer to the stack.
 * @value: value to be pushed onto the stack.
 */
void push_node(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;

	if (*stack != NULL)
	{
		new_node->next = *stack;
		(*stack)->prev = new_node;
	}

	*stack = new_node;
}
/**
 * pall - this function push an int on top of the stack
 * @stack:ouble pointer to the stack.
 * @line_number: line number.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	printf("from pall : print all values on the stack\n");
	(void)stack;
	(void)line_number;
}
