#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
//#include <../matplotlibcpp.h>

using namespace std;

int matrix[3][10], i, j, cont;
double erro;
//matrix[0] = x1; matrix[1] = x2; matrix[2] = y
template <size_t size_x1, size_t size_x2>
float Cost(int (&matriz)[size_x1][size_x2]){
    float Ey = 0, Ex1 = 0, Ex2 = 0, Ex1sqr = 0, Ex2sqr= 0, Ex1y = 0, Ex2y = 0, Ex1x2 = 0, Eyiyc;
    float coefb0 = 0, coefb1 = 0, coefb2 = 0, cost = 0;
    for(i = 0; i < 10; i++){
        Ex1 += matriz[0][i];
        Ex2 += matriz[1][i];
        Ey += matriz[2][i]; 
        Ex1sqr += pow(matriz[0][i], 2);
        Ex2sqr += pow(matriz[1][i], 2);
        Ex1y += (matriz[0][i]*matriz[2][i]);
        Ex2y += (matriz[1][i]*matriz[2][i]);
        Ex1x2 += (matriz[0][i]*matriz[1][i]);
    }

    coefb1 = (Ex2sqr * Ex1y - Ex1x2 * Ex2y)/(Ex1sqr * Ex2sqr - pow(Ex1x2, 2));
    coefb2 = (Ex1sqr * Ex2y - Ex1x2 * Ex1y)/(Ex1sqr * Ex2sqr - pow(Ex1x2, 2));
    coefb0 = Ey - coefb1 * Ex1 - coefb2 * Ex2;

    for(i = 0; i < 10; i++){
        Eyiyc += pow((matriz[2][i] - (coefb0 + coefb1 * matriz[0][i] + coefb2 * matriz[1][i])), 2);
    }

    cost = Eyiyc/(2*10);

    cout << cost << "\n";
   
    return 0.0;
    

}

template <size_t size_x1, size_t size_x2>
int Probability(int (&matriz)[size_x1][size_x2], float theta0, float theta1, float theta2){
    float prob;

    for(j = 0; j < 10; j++){
        prob = 1/(1+exp(-(theta0 + theta1*matriz[0][j] + theta2*matriz[1][j])));
        cout << prob*100 <<endl;
    }
    
    
    return 0;

}

template <size_t size_x1, size_t size_x2>
int Training(int (&matriz)[size_x1][size_x2], float LR){
     double coefb0, coefb1, coefb2;
    for(i = 0; i < 40; i++){
        int idx = i % 10;
        double p = coefb0 + coefb1 * matrix[0][idx] + coefb2 * matrix[1][idx];
        erro = p - matrix[2][idx];
        coefb0 = coefb0 - LR * erro;
        coefb1 = coefb1 - LR * erro * matrix[0][idx];
        coefb2 = coefb2 - LR * erro * matrix[1][idx];
        cout<<"Coeficientes: B0="<<coefb0<<", B1="<<coefb1<<", B2="<<coefb2<<", error="<<erro<<endl;
    }

}

int main()
{
    srand(time(0));
    cout << (sizeof(matrix)/4)/3 << endl;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 10; j++){
            if(i < 2){
                matrix[i][j] = (rand() % 9) - 4;
            }
            else{
                if((pow(matrix[0][j], 2)*2) < 5){
                    cont++;
                    matrix[2][j] = 1;
                }
                else{
                    matrix[2][j] = 0;
                }
            }
        }
    }

    for(i = 0; i < 10; i++){
            cout << matrix[0][i] << "," << matrix[1][i] << "," << matrix[2][i] << '\t';
            cout << endl;
        
    }

    Probability(matrix, 2, -1, 5);
    Cost(matrix);
    Training(matrix, 0.05);
   


    return 0;
}