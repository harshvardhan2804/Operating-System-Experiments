#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

int vowelCount(char *s)
{
    int num_vowels = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' ||
            s[i] == 'o' || s[i] == 'u' || s[i] == 'A' ||
            s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')
        {
            num_vowels++;
        }
    }

    return num_vowels;
}


int wordCount(char *s)
{
    int num_words = 0;
    char *word = strtok(s, " \n");

    while (word != NULL)
    {
        num_words++;
        word = strtok(NULL, " \n");
    }

    return num_words;
}


int main()
{
    char s[100];
    printf("Enter a sentence: ");
    fgets(s, sizeof(s), stdin);

    pid_t process_id = fork();

    if (process_id < 0)
    {
        fprintf(stderr, "Fork has been failed");
        return 1;
    }
    else if (process_id == 0)
    { // child process
        int num_words = wordCount(s);
        exit(num_words);
    }
    else
    { // parent process
        int num_vowels = vowelCount(s);

        int status;
        wait(&status);

        printf("Number of vowels: %d\n", num_vowels);
        printf("Number of words: %d\n", WEXITSTATUS(status));

        return 0;
    }
}