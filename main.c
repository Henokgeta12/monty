#include "monty.h"

int main(int argc, char *argv[])
{

    FILE *file;
    stack_t *stack;
    char *opcode;
    char line[256];
    int i;
    unsigned int line_number;
    int value;
    size_t len;

    /* Check the number of arguments */
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    /* Open the Monty bytecode file */
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Initialize the stack */
    stack = NULL;

    line_number = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;

        opcode = strtok(line, " \t\n$");
        if (opcode == NULL || opcode[0] == '#')
        {
            continue;
        }

        if (strcmp(opcode, "push") == 0)
        {
            char *value_str = strtok(NULL, " \t\n$");

            if (value_str == NULL)
            {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
            }

            len = strlen(value_str);
            while (len > 0 && value_str[len - 1] == '$')
            {
                value_str[--len] = '\0';
            }

            value = atoi(value_str);

            for (i = 0; value_str[i] != '\0'; i++)
            {
                if (!isdigit((unsigned char)value_str[i]) && value_str[i] != '-')
                {
                    fprintf(stderr, "L%u: usage: push integer (got '%s')\n", line_number, value_str);
                    exit(EXIT_FAILURE);
                }
            }

            push(&stack, value);
        }
        else if (strcmp(opcode, "pall") == 0)
        {
            pall(&stack);
        }
        else if (strcmp(opcode, "pint") == 0)
        {
            pint(&stack, line_number);
        }
        else if (strcmp(opcode, "pop") == 0)
        {
            pop(&stack, line_number);
        }
        else if (strcmp(opcode, "swap") == 0)
        {
            swap(&stack, line_number);
        }
        else if (strcmp(opcode, "add") == 0)
        {
            add(&stack, line_number);
        }
        else if (strcmp(opcode, "nop") == 0)
        {
            nop(&stack, line_number);
        }
        else if (strcmp(opcode, "sub") == 0)
        {
            sub(&stack, line_number);
        }
        else if (strcmp(opcode, "div_op") == 0)
        {
            div_op(&stack, line_number);
        }
        else if (strcmp(opcode, "mul") == 0)
        {
            mul(&stack, line_number);
        }
        else if (strcmp(opcode, "mod") == 0)
        {
            mod(&stack, line_number);
        }
        else if (strcmp(opcode, "pchar") == 0)
        {
            pchar(&stack, line_number);
        }
        else if (strcmp(opcode, "pstr") == 0)
        {
            pstr(&stack, line_number);
        }
        else if (strcmp(opcode, "rotl") == 0)
        {
            rotl(&stack, line_number);
        }
        else if (strcmp(opcode, "queue") == 0)
        {
              queue_op(&stack, line_number);
        }
        else if (strcmp(opcode, "stack") == 0)
        {
            stack_op(&stack, line_number);
        }
        else
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);

    return EXIT_SUCCESS;
}
