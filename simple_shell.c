#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * shell_main - Simple UNIX command line interpreter
 *
 * Return: Always 0.
 */
int shell_main(void)
{
char *input;
size_t len = 0;
ssize_t read;

while (1)
{
printf("simple_shell$ ");
read = getline(&input, &len, stdin);
if (read == -1)
{
if (feof(stdin))
{
printf("\n");
free(input);
exit(EXIT_SUCCESS);
}
perror("getline");
exit(EXIT_FAILURE);
}
input[read - 1] = '\0';
if (fork() == 0)
{
if (execlp(input, input, (char *)NULL) == -1)
{
perror("execve");
exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}
}
return (0);
}

