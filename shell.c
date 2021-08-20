#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pair.h"

//TODO
//Find dir
//Find file

/*
  Function Declarations for builtin shell commands:
 */
int cd(char **args);
int help(char **args);
int shell_exit(char **args);
int shell_exit(char **args);
int shell_mkdir(char **args);
int shell_launch(char **args);
int add(char **args);
int sub(char **args);
int multiply(char **args);
int derive(char **args);
int integrate(char **args);
int dot_product(char **args);
int cross_product(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "quit",
    "mkdir",
    "add",
    "sub",
    "mult",
    "dx",
    "int",
    "dot",
    "cross"};

int (*builtin_func[])(char **) = {
    &cd,
    &help,
    &shell_exit,
    &shell_exit,
    &shell_mkdir,
    &add,
    &sub,
    &multiply,
    &derive,
    &integrate,
    &dot_product,
    &cross_product

};

int num_builtins()
{
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int cd(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  }
  else
  {
    if (chdir(args[1]) != 0)
    {
      perror("lsh");
    }
  }
  return 1;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int help(char **args)
{
  int i;
  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < num_builtins(); i++)
  {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int shell_exit(char **args)
{
  return 0;
}
/**
 * I dont know what mode 1 does. probably should
 * This makes a directory
 */
int shell_mkdir(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "lsh: expected argument to \"mdkir\"\n");
  }
  else
  {
    if (mkdir(args[1], 1) != 0)
    {
      perror("lsh");
    }
  }
}
/**Adding an addition function for numbers
 * maybe try to count the number of arguments so i can add 2+2+2 
 * 
 */
int add(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "excepted argument to \"add\"\n");
  }
  else
  {
    double sum = 0;
    int i = 1;
    while (args[i] != NULL)
    {
      sum += strtod(args[i], NULL);
      i++;
    }
    fprintf(stdout, "Result is %g\n", sum);
  }
}

int sub(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "excepted argument to \"sub\"\n");
  }
  else
  {
    double value = strtod(args[1], NULL);
    int i = 2;

    while (args[i] != NULL)
    {
      value -= strtod(args[i], NULL);
      i++;
    }
    fprintf(stdout, "Result is %g\n", value);
  }
}

int multiply(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "excepted argument to \"mult\"\n");
  }
  else
  {
    double sum = 1;
    int i = 1;
    while (args[i] != NULL)
    {
      sum *= strtod(args[i], NULL);
      i++;
    }
    fprintf(stdout, "Result is %g\n", sum);
  }
}

int derive(char **args)
{
  int entries = 6;
  char *inputs[6] = {"sin", "cos", "tan", "cot", "sec", "csc"};
  char *results[6] = {"cos", "-sin", "sec^2", "-csc^2", "sec*tan", "-csc*cot"};

  if (args[1] == NULL)
  {
    fprintf(stderr, "excepted argument to \"dx\"\n");
  }
  else
  {
    char *result;
    for (size_t i = 0; i < entries; i++)
    {
      if (!strcmp(inputs[i], args[1]))
      {
        result = results[i];
        break;
      }
    }
    printf("%s\n", result);
  }
}

int integrate(char **args)
{
  int entries = 6;
  char *inputs[6] = {"1/x", "a^x", "tan", "cot", "cos", "sin"};
  char *results[6] = {"ln(x) + c", "(1/ln(x)) * a ^ x", "-ln |cos(x)|", "ln |sin(x)|", "sin(x)", "-cos(x)"};

  if (args[1] == NULL)
  {
    fprintf(stderr, "excepted argument to \"dx\"\n");
  }
  else
  {
    char *result;
    for (size_t i = 0; i < entries; i++)
    {
      if (!strcmp(inputs[i], args[1]))
      {
        result = results[i];
        break;
      }
    }
    printf("%s + c\n", result);
  }
}

struct vector
{
  int size;
  int arr[];
};

int dot_product(char **args)
{
  struct vector *v1;
  printf("What is the dimension of the vectors: ");
  int dem;
  scanf("%d", &dem);

  v1 = malloc(sizeof(struct vector) + sizeof(int) * dem);

  v1->arr[dem];
  printf("\nEnter vals for v1: \n");
  for (int i = 0; i < dem; i++)
  {
    printf("val: ");
    int val;
    scanf("%d", &val);
    v1->arr[i] = val;
  }
  struct vector *v2;
  v2 = malloc(sizeof(struct vector) + sizeof(int) * dem);
  printf("\nEnter vals for v2: \n");
  for (size_t i = 0; i < dem; i++)
  {
    printf("val: ");
    int val;
    scanf("%d", &val);
    v2->arr[i] = val;
  }

  int sum = 0;

  for (size_t i = 0; i < dem; i++)
  {
    sum += (v1->arr[i] * v2->arr[i]);
  }

  for (size_t i = 0; i < dem; i++)
  {
    printf("%d ", v1->arr[i]);
  }
  printf("\n");
  for (size_t i = 0; i < dem; i++)
  {

    printf("%d ", v2->arr[i]);
  }

  printf("\nThe dot product is %d", sum);

  return 0;
}

int cross_product(char **args)
{
  struct vector *v1;

  int dem = 3;

  v1 = malloc(sizeof(struct vector) + sizeof(int) * dem);

  printf("Enter vals for v1: \n");
  for (int i = 0; i < dem; i++)
  {
    printf("val: ");
    int val;
    scanf("%d", &val);
    v1->arr[i] = val;
  }
  struct vector *v2;
  v2 = malloc(sizeof(struct vector) + sizeof(int) * dem);
  printf("\nEnter vals for v2: \n");
  for (size_t i = 0; i < dem; i++)
  {
    printf("val: ");
    int val;
    scanf("%d", &val);
    v2->arr[i] = val;
  }
  struct vector *v3;
  v3 = malloc(sizeof(struct vector) + sizeof(int) * dem);
  v3->arr[0] = (v1->arr[1] * v2->arr[2]) - (v1->arr[2] * v2->arr[1]);
  v3->arr[1] = (v1->arr[0] * v2->arr[2]) - (v1->arr[2] * v2->arr[0]);
  v3->arr[1] *= -1;
  v3->arr[2] = (v1->arr[0] * v2->arr[1]) - (v1->arr[1] * v2->arr[0]);

  for (size_t i = 0; i < dem; i++)
  {
    printf("%d ", v1->arr[i]);
  }
  printf("\n");
  for (size_t i = 0; i < dem; i++)
  {

    printf("%d ", v2->arr[i]);
  }

  printf("\nThe cross product is.. \n");
  for (size_t i = 0; i < dem; i++)
  {

    printf("%d ", v3->arr[i]);
  }

  return 0;
}
/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */

int shell_launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0)
  {
    // Child process
    if (execvp(args[0], args) == -1)
    {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    // Error forking
    perror("lsh");
  }
  else
  {
    // Parent process
    do
    {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int execute(char **args)
{
  int i;

  if (args[0] == NULL)
  {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < num_builtins(); i++)
  {
    if (strcmp(args[0], builtin_str[i]) == 0)
    {
      return (*builtin_func[i])(args);
    }
  }

  return shell_launch(args);
}

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *read_line(void)
{
#ifdef USE_STD_GETLINE
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  if (getline(&line, &bufsize, stdin) == -1)
  {
    if (feof(stdin))
    {
      exit(EXIT_SUCCESS); // We received an EOF
    }
    else
    {
      perror("lsh: getline\n");
      exit(EXIT_FAILURE);
    }
  }
  return line;
#else
#define RL_BUFSIZE 1024
  int bufsize = RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    // Read a character
    c = getchar();

    if (c == EOF)
    {
      exit(EXIT_SUCCESS);
    }
    else if (c == '\n')
    {
      buffer[position] = '\0';
      return buffer;
    }
    else
    {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize)
    {
      bufsize += RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer)
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
#endif
}

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a\""

/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **split_line(char *line)
{
  int bufsize = TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token, **tokens_backup;

  if (!tokens)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TOK_DELIM);
  while (token != NULL)
  {
    tokens[position] = token;
    position++;

    if (position >= bufsize)
    {
      bufsize += TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char *));
      if (!tokens)
      {
        free(tokens_backup);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

/**
   @brief Loop getting input and executing it.
 */
void loop(void)
{
  char *line;
  char **args;
  int status;

  do
  {
    printf("> ");
    line = read_line();
    args = split_line(line);
    status = execute(args);

    free(line);
    free(args);
  } while (status);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}