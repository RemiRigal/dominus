#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <errno.h>

int main (int argc, char* argv[]){
  if (argc < 2){

        printf("Error, missing arguments\n");
        printf("Convention: \n");
        printf("./gpio_switch pin value\n");
        return EXIT_SUCCESS;

  }else{
        int valueFile;
        char refPath[256];
        sprintf(refPath, "/sys/class/gpio/gpio%s", argv[2]);
        char valuePath[256];
        sprintf(valuePath, "%s/value", refPath);

        if ((valueFile = open(valuePath)) < 0) {
            if (errno == ENOENT){
                int exportFile;
                if ((exportFile = open("/sys/class/gpio/export", O_WRONLY)) < 0){
                    return EXIT_FAILURE;
                } 

                write(exportFile, argv[1], sizeof(argv[1]));
                close(exportFile);

                char directionPath[256];
                sprintf(directionPath, "%s/direction", refPath);
                int directionFile = open(directionPath, O_WRONLY);
                char* direction = "out";
                write(directionFile, direction, sizeof(direction));
                close(directionFile);
            
            }else{
                return EXIT_FAILURE;
            }
        }
        
        write(valuePath, argv[2], sizeof(argv[2]));
        close(valueFile);
  }
}
