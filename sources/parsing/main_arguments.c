// #include "../inc/Cube3D.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t num)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if (num == 0)
		return (0);
	while ((i < num - 1) && (ptr1[i] != '\0' && ptr2[i] != '\0')
		&& (ptr1[i] == ptr2[i]))
		i++;
	return (ptr1[i] - ptr2[i]);
}


/* ---------------------------------------------------------------
* @brief: To allow the user to handle incorrect inputs
* @return: Should throw an error when the argument fails more than 2 
------------------------------------------------------------------*/
char* read_arguments_valid(char **argv)
{
    int i = 0; 

    while(argv[i] != 0)
    {
        int length;

        length = 0;
        while(argv[i][length] != '\0')
            length++;
        if(length >= 4 && ft_strncmp(argv[i] + length - 4, ".cub", 4) == 0)
            printf("Found you\n");
        else
            printf("Error\n");
        i++;
    }
}

int main(int argc, char **argv)
{

    if (argc > 2)
    {
        printf("Too many arguments. Only the second argument will be accepted.\n");
    }
    else if (argc > 1)
    {
        read_arguments_valid(argv);
    }
    else
    {
        printf("No arguments provided.\n");
    }
}