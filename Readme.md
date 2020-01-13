# Like Rabbits
At its core, this is a Genetic Algorithm  
It uses rabbits to simulate evolution to best fit their enviorment  

## Current Features
- Three premade rabbits (Fluffy, Ninja and Standard)  
- Two premade enviorment (Standard and Snowy)  
- Three different special traits that will randomly mutate  
- Generation Logs (See what happened each generation cleanly)

## Next To Be Added
- More Enviorments and Rabbits 

## What Doesn't Work
- Loading a previous Evolution 
- Custom Rabbits / Enviorments

## HOW TO COMPILE
> g++ ./src/driver.cxx ./src/rabbit.cxx ./src/enviorment.cxx ../src/rabbit\_log.cxx -o rabbits <br/>

OR! Use my "make" file (Not a real make file but it does what it needs to!)  
run with...
> chmod +x make  
> ./make

To Run..
> ./rabbits

(Assuming GNU/Linux Distrobution)

## PICTURES!
Main Menu <br/><br/>
![Alt text](./img/main_menu.png)  

Rabbit Selection <br/><br/>
![Alt text](./img/rabbit_select.png)  

Enviorment Selectiong <br/><br/>
![Alt text](./img/env_select.png)

DNA Chart<br/><br/>
![Alt text](./img/chart.png)

