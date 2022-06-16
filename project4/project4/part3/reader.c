#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
    int fd1;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char str1[100],correct[100];
    while (1)
    {
        // First open in read only and read
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, str1, 100);
        
     for(int i=0;i<100;i++)
    {
        if(islower(str1[i])>0)
          correct[i]=toupper(str1[i]);
        else{
            if(isupper(str1[i])>0)
            {
                correct[i]=tolower(str1[i]);
            }
	    else correct[i]=str1[i];
        }
    }
    correct[101]='\0';
        // Print the read string and close
        printf("OutPut: %s\n",correct);
        memset(correct, 0, 101);
        memset(str1,0,100);
        close(fd1);

    }
    return 0;
}
