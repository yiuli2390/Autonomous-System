# Autonomous-System
Solving the Capacitated Vehicle Routing Problem

### Introduction
The Capacitated Vehicle Routing Problem is to find an efficient solution to deliver the goods to the shops in a shortest distance between 249 customers. The goods are delivery by the trucks start from the depot. On each route the truck has been assigned the same amount of 500 capacities for each routine to satisfy as much customers as it can without overlaps.

### Objective
The objective is to solve the vehicle routing problem to get the shortest distance between 249 customers and 1 depot travelling around by the trucks. Each truck is starting from the depot in the beginning and has 500 capacities on each routine and they cannot visit the same customer twice because it is inefficient repeating location.

Original map:
![image](https://github.com/yiuli2390/Autonomous-System/blob/master/Assets/original%20map.png){:height="250px" width="250px"}

My best solution map:
![image](https://github.com/yiuli2390/Autonomous-System/blob/master/Assets/Best%20solution%20map.png){:height="50%" width="50%"}

### Hillclimb
Hillclimb is a method of local search that use to optimize problems. The concept is to find a better solution to a problem within the neighbourhood from the start at the base of a hill, and then repeatedly improve
Simulation annealing

#### Steps
1. First compute the original route from 1-249 to initialize the first value and to compare the next fitness value.
2. Randomly pick two numbers from between 1-249 customers and swap them around.
3. Compute the new route after switched.
4. Compare the current new route to the previous route.
5. If the current route distance is less than the previous which means it is fittest and use that route.
6. Repeat step 1.
