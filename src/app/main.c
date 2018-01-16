#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "../lib/gpio/gpio_switch.h"


int main (int argc, char* argv[]){
    if (argc < 3) {
        printf("Error, missing arguments\n");
        printf("Convention: \n");
        printf("./main pin value\n");
        return EXIT_SUCCESS;
    } else {
        if (setGPIOValue(argv[1], argv[2]) == EXIT_FAILURE) {
            if (initGPIO(argv[1]) == EXIT_FAILURE) {
                return EXIT_FAILURE;
            }
            if (setGPIODirection(argv[1], "out") == EXIT_FAILURE) {
                return EXIT_FAILURE;
            }
            if (setGPIOValue(argv[1], argv[2]) == EXIT_FAILURE) {
               return EXIT_FAILURE;
            }         
        }
        return EXIT_SUCCESS;
    }
}
