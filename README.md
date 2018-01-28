# DOMINUS

The aim of this project is to create nearly from scratch our own operating system and to use it on a raspberry pi to exectute some simple tasks. 
Here the task consits on switching a LED on/off when clicking on a domoticz switch, by the use of a relay.

## Src

This folder contains our sources for the project. Here are the different folders :

* app contains the main programs which start the application

* domoticz contains the example create_sensor which create a virtual sensor on domoticz

* lib contains the following libraries :
    * gpio which contains the gpio_switch library for the creation and control of the gpios

* scripts contains the following shells :
    * switch_off and switch_on which calls the gpio_switch library to control the LED


## Relay's Schematics  

Here is the relay schematics of the connections to the raspberry pi.

<p align="center">
  <img src="https://github.com/RemiRigal/dominus/tree/PCMR/img/relay_schematics.png" width="350" title="Relay connections schema">
</p>


## Docker

This file allows you to create an image based on a debian image, and that automatically download and compile the buildroot for the RPi3.

This image includes :
* A root session which password is `toor`
* A user session which name is `user_1` and password `user_1pw`
* Domoticz is installed and automatically starts when the RPi3 boots.

In order to creates this docker, you just have to run this command line where the .dockerfile is :

		docker build .

You can give the image a name with the `-t` option.

NB : The whole running of this command took me about 40 minutes. It works (and have been tested) with a stable internet connexion (there are not the settings for the ENSTA's proxy, and it doesn't work with the unstable wifi connexion of the school).


The ID of the image is returned at the end of the running of the build command. Otherwise, you can find it by running this command :

		docker image ls

After that, you can create a docker container from the image by running :

		docker run -it <image_ID> 

The image for the sdcard can be found in `/root/buildroot-2017.08/outputs/image`. 
You can also copy it by running :

		docker cp <docker_ID>:/root/buildroot-2017.08/output/images/sdcard.img .

