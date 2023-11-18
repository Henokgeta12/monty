#include "monty.h"


/**
 * mod - Computes the remainder of the division of the second top element by
 * the top element of the stack.
 * @stack: Double pointer to the stack
 * @line_number: Line number being executed
 */


void mod(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n %= (*stack)->n;

    pop(stack, line_number);
}


/**
 * pchar - Prints the ASCII character corresponding to the top element of the stack.
 * @stack: Double pointer to the stack
 * @line_number: The Line number are being executed.
 */


void pchar(stack_t **stack, unsigned int line_number)
{
    
   int ascii_value;
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    ascii_value = (*stack)->n;

    if (ascii_value < 0 || ascii_value > 127)
    {
        fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%c\n", (char)ascii_value);
}


/**
 * pstr - Prints the string starting from the top of the stack.
 * @stack: Double pointer to the stack
 * @line_number: Line number being executed
 */


void pstr(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;

    while (current != NULL && current->n != 0 && current->n >= 0 && current->n <= 127)
    {
        printf("%c", (char)current->n);
        current = current->next;
    }
    (void)line_number;

    printf("\n");
}


/**
 * rotl - Rotates the stack to the top.
 * @stack: Double pointer to the stack
 * @line_number: Line number being executed
 */


void rotl(stack_t **stack, unsigned int line_number)
{
    if (*stack != NULL && (*stack)->next != NULL)
    {
        stack_t *top = *stack;
        stack_t *second_top = (*stack)->next;
        stack_t *bottom = *stack;

        while (bottom->next != NULL)
        {
            bottom = bottom->next;
        }

        *stack = second_top;
        second_top->prev = NULL;
        bottom->next = top;
        top->prev = bottom;
        top->next = NULL;
    }
    (void)line_number;
}
