#include <stdio.h>

double calculate_pressure_on_block(int row, int column, double block_weight);


double helper(int row, int column, double block_weight){
    double result, k = (double)15/100;
    int i = row - column;
    if (row == 0 && column == 0){
        result = 0.00000000;
        return result;
    }
    else if (column == 0){
        result = (double)block_weight/2 + (k)*helper(row-1,0,block_weight);
        return result;
    }
    else if (i == 0){
        result = (double)block_weight/2 + (k)*helper(row-1, i,block_weight);
        return result;
    }
    else{
        result = block_weight +  (k)*helper(row-1,i-1,block_weight) +  (k)*helper(row-1,i,block_weight);
        return result;
        
    }
    
}

double calculate_pressure_on_block(int row, int column, double block_weight){
    if(column == 0 && row == 0){
        printf("(%d,%d) %.8f\n",row, column, helper(row, column,block_weight));
        return 0.0;
    }
    else if(column == 0){
        calculate_pressure_on_block(row-1,row-1,block_weight);
        printf("(%d,%d) %.8f\n", row, column, helper(row, column, block_weight));
        return 0.0;
    }
    else{
        calculate_pressure_on_block(row,column-1,block_weight);
        printf("(%d,%d) %.8f\n", row, column, helper(row, column, block_weight));
        return 0.0;
    }
}


int main() {
    int N, W;
    scanf("%d %d", &N, &W);
    calculate_pressure_on_block(N-1,N-1,(double)W);
    return 0;
}