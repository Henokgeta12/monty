#include "monty.h"

/**
 * push - Pushes an element onto the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Line Number in the Monty byte code file
 * @value: Integer Value to push to the stack
 */

void push(stack_t **stack, int value)
{
    if (get_mode() == STACK_MODE)
    {
        stack_t *new_node = malloc(sizeof(stack_t));
        if (new_node == NULL)
        {
            fprintf(stderr, "Error: malloc failed\n");
            exit(EXIT_FAILURE);
        }

        new_node->n = value;
        new_node->prev = NULL;

        new_node->next = *stack;

        if (*stack != NULL)
        {
            (*stack)->prev = new_node;
        }

        *stack = new_node;
    }
    else if (get_mode() == QUEUE_MODE)
    {
        queue_push(stack, value);
    }
}



/**
 * pall - Prints all values on the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Line number in the Monty byte code file
 */
void pall(stack_t **stack)
{
    stack_t *current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}



void pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}


void pop(stack_t **stack, unsigned int line_number)
{
    stack_t *tmp;
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    tmp = *stack;
    *stack = tmp->next;

    if (*stack != NULL)
    {
        (*stack)->prev = NULL;
    }

    free(tmp);
}

void swap(stack_t **stack, unsigned int line_number)
{
     int temp;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    temp = (*stack)->n;
    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = temp;
}
