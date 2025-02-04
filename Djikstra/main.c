#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define infinite 100000
#define num_cities 9

//Cost matrix gösterimini yapmak icin gerekli fonksiyon
void print_cost_matrix(int minimum[9][9]){
    for(int i = 0; i < num_cities; i++){
        printf("%d\t", i+1);
    }
        
    printf("\n\t");

    for(int i=0; i < num_cities; i++){
        printf("--\t");
    }
        
    for(int i = 0; i < num_cities ; i++){
        printf("\n%d|\t", i+1);

        for(int j = 0; j < num_cities; j++){
            if(minimum[i][j] != -1){
                printf("%d\t", minimum[i][j]);
            }
                
            else{
                printf("-\t");
            }
        }
    }

}

// Iki sehir arası en kısa yolu bulmak için kullanacağımız Dıjkstra's algoritması fonksiyonu 
void dijkstra(int matrix[9][9], int matrix2[9][9], int src, int dest)
{
    int minimum[9][9];
    
    for(int i = 0; i < num_cities; i++){
        for(int j = 0; j < num_cities; j++){
            minimum[i][j] = matrix[i][j];
        }
    } 

    for(int k = 0; k < num_cities; k++){
        for(int i = 0; i < num_cities; i++){
            for(int j = 0; j < num_cities; j++){
                if(minimum[i][k] + minimum[k][j] < minimum[i][j]){
                    minimum[i][j] = minimum[i][k] + minimum[k][j];
                }
            }
        }
    }

    for(int i = 0; i < num_cities; i++){
        for(int j = 0; j < num_cities; j++){
            if(i == j){
                minimum[i][j] = -1;
            }
        }
    }

    printf("1st option (Cost Matrix):\n\t");
    //1. Matrisi yapistiralim
    print_cost_matrix(minimum);
    
    printf("\n\n");

    int minimum2[9][9];

    for(int i = 0; i < num_cities; i++){
        for(int j = 0; j < num_cities; j++){
            minimum2[i][j] = matrix2[i][j];
        }
    } 

    for(int k = 0; k < num_cities; k++){
        for(int i = 0; i < num_cities; i++){
            for(int j = 0; j < num_cities; j++){
                if(minimum2[i][k] + minimum2[k][j] < minimum2[i][j]){
                    minimum2[i][j] = minimum2[i][k] + minimum2[k][j];
                }
            }
        }
    }

    for(int i = 0; i < num_cities; i++){
        for(int j = 0; j < num_cities; j++){
            if(i == j){
                minimum2[i][j] = -1;
            }   
        }
    }
    
    printf("2nd option (Cost Matrix):\n\t");
    //2. Matrisi yapistiralim
    print_cost_matrix(minimum2);
    
    if(minimum[src][dest] > minimum2[src][dest]){
        printf("\nThe best option for the flight is the second one (%d < %d)\n", minimum2[src][dest] ,minimum[src][dest] );
    }
    else if(minimum[src][dest] <= minimum2[src][dest]){
        printf("\nThe best option for the flight is the first one (%d >= %d)\n",minimum2[src][dest], minimum[src][dest]);
    }
}

int main()
{
    // Sehirler
    printf("Cities:\n");
    printf("1. Gaziantep\n");
    printf("2. Adana\n");
    printf("3. Izmir\n");
    printf("4. Eskisehir\n");
    printf("5. Ankara\n");
    printf("6. Antalya\n");
    printf("7. Trabzon\n");
    printf("8. Kars\n");
    printf("9. Istanbul\n");

    // Kullanicidan gidilecek hedef ve baslangic noktasi secimi istenmesi
    int src ,dest;
    printf("From? (Please enter the city code): ");
    scanf("%d", &src);
    src--;
    printf("To? (Please enter the city code): ");
    scanf("%d", &dest);
    dest--;

    // 1. Sirket icin komsuluk matrisi 
    int matrix1[9][9] = {
        {infinite, 10, infinite, infinite, infinite, infinite, infinite, 40, infinite},
        {10, infinite, 10, infinite, infinite, infinite, infinite, infinite, 30},
        {infinite, 10, infinite, 20, 100, infinite, infinite, infinite, 100},
        {infinite, infinite, 20, infinite, 30, infinite, infinite, infinite, infinite},
        {infinite, infinite, 100, 30, infinite, 50, infinite, infinite, 30},
        {infinite, infinite, infinite, infinite, 50, infinite, infinite, infinite, 50},
        {infinite, infinite, infinite, infinite, infinite, infinite, infinite, 30, 70},
        {40, infinite, infinite, infinite, infinite, infinite, 30, infinite, 20},
        {infinite, 30, 100, infinite, 30, 50, 70, 20, infinite}
    };

    // 2. Sirket icin komsuluk matrisi
    int matrix2[9][9] = {
        {infinite, 20, infinite, infinite, infinite, infinite, infinite, 20, infinite},
        {20, infinite, 40, infinite, infinite, infinite, infinite, infinite, 30},
        {infinite, 40, infinite, 30, 100, infinite, infinite, infinite, 15},
        {infinite, infinite, 30, infinite, 10, infinite, infinite, infinite, infinite},
        {infinite, infinite, 100, 10, infinite, 30, infinite, infinite, 20},
        {infinite, infinite, infinite, infinite, 30, infinite, infinite, infinite, 50},
        {infinite, infinite, infinite, infinite, infinite, infinite, infinite, 60, 60},
        {20, infinite, infinite, infinite, infinite, infinite, 60, infinite, 20},
        {infinite, 30, 15, infinite, 20, 50, 60, 20, infinite}
    };

    // Dijkstra's algoritması kullanilarak en kisa yolu bulmak icin cagirdigimiz fonksiyon 
    dijkstra(matrix1, matrix2, src, dest);


    return 0;
}


