#include <stdio.h>
int main() {
    
    int i,j, N, M, parties[26], seats[26] = {0}, maxindex;
    float max, current;
    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    scanf("%d %d",&N,&M);
    
    for(i = 0; i < N ; i++){
        scanf("%d",&parties[i]);
    }
    for(j = 0; j < M; j++){
        for(i = 0; i < N; i++){
            current = (float)parties[i]/(seats[i]+1);
            if(i == 0){
                max = current;
                maxindex = i;
            }
            else if(current == max){
                if (parties[maxindex] < parties[i]){
                    max = current;
                    maxindex = i;
                }
            }
            else if(current > max){
                max = current;
                maxindex = i;
            }
            
        }
        seats[maxindex] += 1;
        
    }
    
    for(j = 0; j < N; j++){
        for(i = 0; i < N; i++){
            if(i == 0){
                max = seats[i]; 
                maxindex = i;
            }
            else if(seats[i] > max){
                max = seats[i];
                maxindex = i;
            }
        }
        if(max != 0){
            printf("%c: %d\n",alphabet[maxindex], seats[maxindex]);
            seats[maxindex] = 0;
        }
    
        
    }
    
    
    return 0;
}