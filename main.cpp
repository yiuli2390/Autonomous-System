#include <iostream>
#include <Math.h>
#include <fstream>
#include <iomanip>
//in this assignment i used hill climbling + simulation annealing
using namespace std;

//initializing the values
static const int VEHICLE_CAPACITY = 500;
static const int NUM_NODES = 251;
static const int NUM_COORDINATE_DIMENSIONS = 2;
static const int X_COORDINATE = 0; // x-axis coordinate is dimension 0 in coords[][]
static const int Y_COORDINATE = 1; // y-axis coordinate is dimension 1 in coords[][]

int coords[NUM_NODES][NUM_COORDINATE_DIMENSIONS] =
        {{0,0},
         {-33,33},{-99,-97},{-59,50},{0,14},{-17,-66},{-69,-19},{31,12},{5,-41},{-12,10},{-64,70},
         {-12,85},{-18,64},{-77,-16},{-53,88},{83,-24},{24,41},{17,21},{42,96},{-65,0},{-47,-26},
         {85,36},{-35,-54},{54,-21},{64,-17},{55,89},{17,-25},{-61,66},{-61,26},{17,-72},{79,38},
         {-62,-2},{-90,-68},{52,66},{-54,-50},{8,-84},{37,-90},{-83,49},{35,-1},{7,59},{12,48},
         {57,95},{92,28},{-3,97},{-7,52},{42,-15},{77,-43},{59,-49},{25,91},{69,-19},{-82,-14},
         {74,-70},{69,59},{29,33},{-97,9},{-58,9},{28,93},{7,73},{-28,73},{-76,55},{41,42},
         {92,40},{-84,-29},{-12,42},{51,-45},{-37,46},{-97,35},{14,89},{60,58},{-63,-75},{-18,34},
         {-46,-82},{-86,-79},{-43,-30},{-44,7},{-3,-20},{36,41},{-30,-94},{79,-62},{51,70},{-61,-26},
         {6,94},{-19,-62},{-20,51},{-81,37},{7,31},{52,12},{83,-91},{-7,-92},{82,-74},{-70,85},
         {-83,-30},{71,-61},{85,11},{66,-48},{78,-87},{9,-79},{-36,4},{66,39},{92,-17},{-46,-79},
         {-30,-63},{-42,63},{20,42},{15,98},{1,-17},{64,20},{-96,85},{93,-29},{-40,-84},{86,35},{91,36},{62,-8},{-24,4},
         {11,96},{-53,62},{-28,-71},{7,-4},{95,-9},{-3,17},{53,-90},{58,-19},{-83,84},{-1,49},{-4,17},{-82,-3},
         {-43,47},{6,-6},{70,99},{68,-29},{-94,-30},{-94,-20},{-21,77},{64,37},{-70,-19},{88,65},{2,29},
         {33,57},{-70,6},{-38,-56},{-80,-95},{-5,-39},{8,-22},{-61,-76},{76,-22},{49,-71},{-30,-68},{1,34},
         {77,79},{-58,64},{82,-97},{-80,55},{81,-86},{39,-49},{-67,72},{-25,-89},{-44,-95},{32,-68},{-17,49},
         {93,49},{99,81},{10,-49},{63,-41},{38,39},{-28,39},{-2,-47},{38,8},{-42,-6},{-67,88},{19,93},{40,27},
         {-61,56},{43,33},{-18,-39},{-69,19},{75,-18},{31,85},{25,58},{-16,36},{91,15},{60,-39},{49,-47},{42,33},
         {16,-81},{-78,53},{53,-80},{-46,-26},{-25,-54},{69,-46},{0,-78},{-84,74},{-16,16},{-63,-14},{51,-77},
         {-39,61},{5,97},{-55,39},{70,-14},{0,95},{-45,7},{38,-24},{50,-37},{59,71},{-73,-96},{-29,72},{-47,12},
         {-88,-61},{-88,36},{-46,-3},{26,-37},{-39,-67},{92,27},{-80,-31},{93,-50},{-20,-5},{-22,73},{-4,-7},
         {54,-48},{-70,39},{54,-82},{29,41},{-87,51},{-96,-36},{49,8},{-5,54},{-26,43},{-11,60},{40,61},{82,35},
         {-92,12},{-93,-86},{-66,63},{-72,-87},{-57,-84},{23,52},{-56,-62},{-19,59},{63,-14},{-13,38},{-19,87},
         {44,-84},{98,-17},{-16,62},{3,66},{26,22},{-38,-81},{70,80},{17,-35},{96,-83},{-77,80},{-14,44}};

int demand[NUM_NODES]= {999,0,6,72,93,28,5,43,1,36,53,63,25,50,57,1,66,37,51,47,88,75,48,40,8,69,93,29,5,53,8,24,53,13,47,57,9,74,83,96,
                        42,80,22,56,43,12,73,32,8,79,79,4,14,17,19,44,5,37,100,62,90,57,44,37,80,60,95,56,56,9,39,15,4,58,73,5,12,3,
                        8,31,48,3,52,99,29,12,50,98,4,56,24,33,45,98,4,36,72,26,71,84,21,99,33,84,74,93,25,39,42,77,68,50,42,71,85,78,
                        64,5,93,18,38,29,81,4,23,11,86,2,31,54,87,17,81,72,10,50,25,71,85,51,29,55,45,100,38,11,82,50,39,6,87,83,22,
                        24,69,97,65,97,79,79,46,52,39,94,97,18,3,23,19,40,49,96,58,15,21,56,67,10,36,84,59,85,60,33,62,70,79,98,99,
                        18,55,75,94,89,13,19,19,90,35,76,3,11,98,92,1,2,63,57,50,19,24,14,18,77,28,72,49,58,84,58,41,98,77,57,39,99,
                        83,54,86,2,14,42,14,55,2,18,17,22,28,3,96,53,15,36,98,78,92,65,64,43,50};

int nodeID[NUM_NODES]= {999, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
                        27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
                        51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
                        75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98,
                        99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117,
                        118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136,
                        137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155,
                        156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174,
                        175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193,
                        194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212,
                        213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231,
                        232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250};

double distance(int node1, int node2){
    int x1, y1, x2, y2;
    double dist;
    x1 = coords[node1][X_COORDINATE];
    y1 = coords[node1][Y_COORDINATE];
    x2 = coords[node2][X_COORDINATE];
    y2 = coords[node2][Y_COORDINATE];
    // compute Euclidean distance
    dist = sqrt(pow((x1-x2),2) + pow((y1-y2),2));
    return dist;
}

void swapRandomNode(int node1, int node2)
{
    int temp;
    temp = nodeID[node1];
    nodeID[node1] = nodeID[node2];
    nodeID[node2] = temp;
    temp = coords[node1][X_COORDINATE];
    coords[node1][X_COORDINATE] = coords[node2][X_COORDINATE];
    coords[node2][X_COORDINATE] = temp;
    temp = coords[node1][Y_COORDINATE];
    coords[node1][Y_COORDINATE] = coords[node2][Y_COORDINATE];
    coords[node2][Y_COORDINATE] = temp;
    temp = demand[node1];
    demand[node1] = demand[node2];
    demand[node2] = temp;
}

double route_Distance(){
    int current_node, prev_node, demands = 0, node_num=250;
    double current_fitness = 0;
    for (int r = 2; r < NUM_NODES; r++) {
        current_node = r;
        prev_node = r - 1;
            if (demands + demand[current_node] < VEHICLE_CAPACITY) { //if add this demands is still less than 500
                current_fitness += distance(prev_node, current_node);
                demands += demand[current_node];
            }
            else {
                current_fitness += distance(1, prev_node);
                current_fitness += distance(1, current_node);  //back to depot and start the next route
                demands = demand[current_node]; // reinitilize the demand back to 0 after go back
            } // Otherwise trucks is full
        if(r == node_num)
        {
            current_fitness += distance(1, current_node); //back to depot
        }
    }//for
    return current_fitness;
}

void writeFile(double cost){
    int node1, demands = 0, node_num=250;
    ofstream best_Route("best-solution.txt");
    best_Route << flush;
    best_Route << "name Yiu Ming Li\n";
    best_Route << "algorithm simulation annealing\n";
    best_Route << std::fixed << std::setprecision(6) << "cost " << cost << "\n";
    for (int r = 1; r < NUM_NODES; r++) {
        node1 = r;
        if(r == node_num)
        {
            best_Route << nodeID[node1] << "->1" <<  "\n";
        }
        else {
            if (demands + demand[node1] < VEHICLE_CAPACITY) { //if add this demands is still less than 500
                demands += demand[node1];
                best_Route << nodeID[node1] << "->";
            }
            else {
                best_Route << "1\n1->";
                demands = 0; // reinitilize the demand back to 0 after go back
                r--;
            }// Otherwise trucks is full
        }//if not 250 carry on loop
    }//for
    best_Route.close();
}

double find_good_Neighbour(double best_fitness){
    int rand_node1, rand_node2, max = 250, min = 2, counter = 0;
    double T, T_min = 0.1, cooling = 0.99999999;
    double  dE, p, c;
    double current_fitness, annealing_fitness = best_fitness;
    srand(time(NULL));

    for(T = 10; T>T_min; T *= cooling){
        rand_node1 = min + rand() % (max - min + 1);
        rand_node2 = min + rand() % (max - min + 1);
        swapRandomNode(rand_node1, rand_node2);
        current_fitness = route_Distance();
        dE = annealing_fitness - current_fitness;
        if (dE >= 0) {
            annealing_fitness = current_fitness;
            if(annealing_fitness < best_fitness) {                          //because using
                best_fitness = annealing_fitness;
                writeFile(best_fitness);
            }
                printf("Annealing: %f\n", annealing_fitness);
        }
        else {
            if (exp(dE / T) > ((double) rand() / (RAND_MAX))) annealing_fitness = current_fitness;
            else swapRandomNode(rand_node1, rand_node2);
        }
            T *= cooling;
        counter++;
    }//loop
    return best_fitness;
}

int main() {
    double bestfitness;
    bestfitness = route_Distance();//original distance
    printf("Original Distance is: %f \n", bestfitness);
//    writeFile(bestfitness);
    bestfitness = find_good_Neighbour(bestfitness);
    printf("Best distance: %f \n", bestfitness);
    return 0;
}