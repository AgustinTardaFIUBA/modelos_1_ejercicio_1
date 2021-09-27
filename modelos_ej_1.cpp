#include <stdio.h>
#include <list>
#include <iterator>
#include <iostream>
#include <fstream>

#define CANT_MAX 50
#define CLOTHES_AMOUNT 20
using namespace std;

void initializeCompatibility(int compatibility[][CLOTHES_AMOUNT]);
void loadCompatibility(int compatibility[][CLOTHES_AMOUNT]);
void initializeWashingMachines(list<int>* washingMachines[]);
bool isCompatible(list<int>* washingMachine,int clothNumber,int compatibility[][CLOTHES_AMOUNT]);
void printClothesInEachMachine(list<int>*washingMachines[] ,int amountOfWashingMachinesUsed);


int main(){
    
    int compatibility [CLOTHES_AMOUNT][CLOTHES_AMOUNT];
    initializeCompatibility(compatibility);
    loadCompatibility(compatibility);

    int amountOfWashingMachinesUsed = 0 ;
    list<int>* washingMachines[CLOTHES_AMOUNT];
    initializeWashingMachines(washingMachines);


    
    for (int i = 0; i < CLOTHES_AMOUNT; i++)
        for (int j = 0; j < CLOTHES_AMOUNT; j++)
            printf("%d",compatibility[i][j]);
    
    for (int clothNumber = 0; clothNumber < CLOTHES_AMOUNT; clothNumber++)
    {
        bool  hasAMchine = false;
        int machineNumber = 0;
        while(!hasAMchine){
            if(washingMachines[machineNumber] == NULL){

                washingMachines[machineNumber] = new list<int>;
                amountOfWashingMachinesUsed++;

                washingMachines[machineNumber]->push_back(clothNumber);
                hasAMchine = true;
                printf("Put cl: %d in: %d",clothNumber, machineNumber);
            }else{
                if(isCompatible(washingMachines[machineNumber],clothNumber,compatibility)){

                    washingMachines[machineNumber]->push_back(clothNumber);
                    hasAMchine = true;
                    printf("Put cl: %d in: %d",clothNumber, machineNumber);
                }
            }

            machineNumber++;
        }
        
    }
    
    printClothesInEachMachine(washingMachines,amountOfWashingMachinesUsed);

    return 0;
}

void loadCompatibility(int compatibility[][CLOTHES_AMOUNT]) {
  char line[CANT_MAX];
  FILE *compatibilityFile = fopen("ej_1_data.txt", "r");

  while (fgets(line, sizeof(line), compatibilityFile)) {
    char type;
    int n1 = 0, n2 = 0;
    sscanf(line, "%c %d %d", &type, &n1, &n2);
    compatibility[n1-1][n2-1] = 0 ;
  }

  fclose(compatibilityFile);
}

void initializeCompatibility(int compatibility[][CLOTHES_AMOUNT] ){
    for (int i = 0; i < CLOTHES_AMOUNT; i++)
        for (int j = 0; j < CLOTHES_AMOUNT; j++)
            compatibility[i][j] = 1;
}

void initializeWashingMachines(list<int>* washingMachines[]){
    for (int i = 0; i < CLOTHES_AMOUNT; i++)
        washingMachines[i] = NULL;
}

bool isCompatible(list<int>* washingMachine,int clothNumber,int compatibility[][CLOTHES_AMOUNT]){
    bool isCompatible = true;
    list<int>::iterator clothesIterator = washingMachine->begin();

    while(isCompatible && (clothesIterator != washingMachine->end())){
        isCompatible =  (compatibility[*clothesIterator][clothNumber] == 1);
        clothesIterator++;
    }

    return isCompatible;
}

void printClothesInEachMachine(list<int>* washingMachines[] ,int amountOfWashingMachinesUsed){

    printf("amount WM: %d\n",amountOfWashingMachinesUsed);

    ofstream resultsFile("results.txt");

    for (int washingMachineNumber = 0; washingMachineNumber < amountOfWashingMachinesUsed; washingMachineNumber++)
    {
        list<int>::iterator clothesIterator = washingMachines[washingMachineNumber]->begin();
        printf("WM number: %d\n",washingMachineNumber);
        while (clothesIterator != washingMachines[washingMachineNumber]->end())
        {   
            char resultLine[10];
            sprintf(resultLine, "%d %d", (*clothesIterator)+1, washingMachineNumber+1);

            resultsFile<<resultLine<< endl;
            printf("%s\n",resultLine);

            clothesIterator++;
        }
        
    }
    resultsFile.close();
    
}


