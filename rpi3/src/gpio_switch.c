#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char* argv[]){
  if (argc < 3){

        printf("Error, missing arguments\n");
        printf("Convention: \n");
        printf("./gpio_switch pin value\n");
        return EXIT_SUCCESS;

  } else {
        int valueFile;
        char refPath[256];
        sprintf(refPath, "/sys/class/gpio/gpio%s", argv[1]);
        char valuePath[256];
        sprintf(valuePath, "%s/value", refPath);

        if ((valueFile = open(valuePath, O_WRONLY)) < 0) {
            if (errno == ENOENT){
                int exportFile;
                if ((exportFile = open("/sys/class/gpio/export", O_WRONLY)) < 0){
                    return EXIT_FAILURE;
                } 

                write(exportFile, argv[1], strlen(argv[1]));
                close(exportFile);

                char directionPath[256];
                sprintf(directionPath, "%s/direction", refPath);
                int directionFile = open(directionPath, O_WRONLY);
                char* direction = "out";
                write(directionFile, direction, strlen(direction));
                close(directionFile);

                valueFile = open(valuePath, O_WRONLY);
            } else {
                return EXIT_FAILURE;
            }
        }
        
        write(valueFile, argv[2], strlen(argv[2]));
        close(valueFile);
  }
}
