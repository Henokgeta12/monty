#include "monty.h"
/**
 * pintdata - this function prints the value at the top of the stack.
 * @stack:ouble pointer to the stack.
 * @line_number: line number.
 */
void pintdata(stack_t **stack, unsigned int line_number)
{
	int top;
	stack_t *temporary = *stack;

	if (temporary == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	while (temporary->next != NULL)
	{
		temporary = temporary->next;
	}
	top = temporary->n;
	printf("%d\n", top);
}
