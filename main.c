#include "monty.h"

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	stack_t *stack;

	if (argc < 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	stack = NULL; /* Initialize the stack */
	if (!processFile(argv[1], &stack))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

/**
 * processFile - Process the commands in the file
 * @filename: Name of the file to process
 * @stack: Double pointer to the stack
 *
 * Return: 1 on success, 0 on failure
 */
int processFile(char *filename, stack_t **stack)
{
	FILE *filePtr;
	char buffer[SIZE];
	int lineNumber = 0;

	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{NULL, NULL}
	};

	filePtr = fopen(filename, "r");
	if (filePtr == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		return (0);
	}

	while (fgets(buffer, sizeof(buffer), filePtr) != NULL)
	{
		lineNumber++;
		printf("at line %d: %s", lineNumber, buffer);

		if (!executeCommand(buffer, lineNumber, stack, instructions))
		{
			fclose(filePtr);
			return (0);
		}
	}

	fclose(filePtr);
	return (1);
}

/**
 * executeCommand - Execute a single command from the buffer
 * @buffer: Buffer containing the command
 * @lineNumber: Current line number
 * @stack: Double pointer to the stack
 * @instructions: Array of valid instructions
 *
 * Return: 1 on success, 0 on failure
 */
int executeCommand(char *buffer, int lineNumber, stack_t **stack, instruction_t *instructions)
{
	char *token;
	int i;

	token = strtok(buffer, " \t\n");
	if (token == NULL)
		return (1);

	for (i = 0; instructions[i].opcode != NULL; i++)
	{
		if (strcmp(token, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, lineNumber);
			return (1);
		}
	}

	fprintf(stderr, "L%d: unknown instruction %s\n", lineNumber, token);
	return (0);
}
