/********************************************************
 * Title: 		    reflect								*
 * Creator: 		  John J. Coleman						*
 * Creation Date:	27.11.2025							*
 * Modified Date:	12.12.2025							*
 *                                                     *
 * Description:                                        *
 * Compare output of files side by side.               *
 * Not complete yet, still a lot of work needed.       *
 *******************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static void read_file(char* path, char* buffer, unsigned int size)
{
	memset(buffer, 0, size);
	int fd = open(path, O_RDONLY);
	read(fd, buffer, size);
	close(fd);
}

static void spacing(int c)
{
	if(c < 8)
		fprintf(stdout, "\t\t\t\t\t\t\t\t\t\t");
	else if(c < 16)
		fprintf(stdout, "\t\t\t\t\t\t\t\t\t");
	else if(c < 24)
		fprintf(stdout, "\t\t\t\t\t\t\t\t");
	else if(c < 32)
		fprintf(stdout, "\t\t\t\t\t\t\t");
	else if(c < 40)
		fprintf(stdout, "\t\t\t\t\t\t");
	else if(c < 48)
		fprintf(stdout, "\t\t\t\t\t");
	else if(c < 56)
		fprintf(stdout, "\t\t\t\t");
	else if(c < 64)
		fprintf(stdout, "\t\t\t");
	else if(c < 72)
		fprintf(stdout, "\t\t");
	else
		fprintf(stdout, "\t");
}

int main(int argc, char* argv[])
{
	char first[16384];
	char second[16384];
	int c, i, j;

	c = i = j = 0;

	read_file(argv[1], first, sizeof(first));
	read_file(argv[2], second, sizeof(second));

	while(first[i] != '\0')
	{
		if(first[i] == '\n')
		{
			spacing(c);

			while(second[j] != '\0')
			{
				if(second[j] == '\n')
				{
					fprintf(stdout, "\n");
					j++;
					break;
				}
				else if(second[j] == '\t')
				{
					second[j] = ' ';
					j++;
				}
				else
				{
					fprintf(stdout, "%c", second[j]);
					j++;
				}
			}

			i++;
			c = 0;
			continue;
		}
		else if(first[i] == '\t')
		{
			first[i] = ' ';
			c++;
			i++;
		}
		else
		{
			fprintf(stdout, "%c", first[i]);
			c++;
			i++;
		}
	}

	fprintf(stdout, "\n\n");
	
	return 0;
}
