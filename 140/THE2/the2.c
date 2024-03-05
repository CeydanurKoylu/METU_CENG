#include <stdio.h>
#include <stdlib.h>

/*My original path finder function that uses depth first search but takes too much time on large inputs:*/

int pathfinder(char **labyr, int width, int height, int currx, int curry){
    
    labyr[curry][currx] = '*';
    
    if((currx == (width-1)) || (curry == (height-1)) || (currx == 0) || (curry == 0)){
        return 1;
        
    }
    if(((curry-1)>= 0) && currx<width && (labyr[curry-1][currx] == ' ')){
        if(pathfinder(labyr,width,height,currx,curry-1)){
            return 1;
        }
    }
    
    if(((curry+1)<height) && currx<width && (labyr[curry+1][currx] == ' ')){
        if(pathfinder(labyr,width,height,currx,curry+1)){
            return 1;
        }
        
    }
    
    if(((currx+1) < width) && curry<height && (labyr[curry][currx+1] == ' ')){
        if(pathfinder(labyr,width,height,currx+1,curry)){
            return 1;
        }
       
    }
    if(((currx-1)>=0) && curry<height && (labyr[curry][currx-1] == ' ')){
        if(pathfinder(labyr,width,height,currx-1,curry)){
            return 1;
        }
        
    }
    
    labyr[curry][currx]=' ';
    return 0;
        
    
}

/*Filler function which fills up the whole space one can reach by using the available passage cells:*/

void filler(char** labyr,int width,int height,int currx,int curry,char*is_found){
    labyr[curry][currx] = '.';
    
    if(((curry-1)>= 0) && currx<width && (labyr[curry-1][currx] == ' ')){
        filler(labyr,width,height,currx,curry-1,is_found);
    }
    if(((curry+1)<height) && currx<width && (labyr[curry+1][currx] == ' ')){
        filler(labyr,width,height,currx,curry+1,is_found);
        
    }
    if(((currx+1) < width) && curry<height && (labyr[curry][currx+1] == ' ')){
        filler(labyr,width,height,currx+1,curry,is_found);
       
    }
    if(((currx-1)>=0) && curry<height && (labyr[curry][currx-1] == ' ')){
        filler(labyr,width,height,currx-1,curry,is_found);
        
    }
    
    if((currx == (width-1)) || (curry == (height-1)) || (currx == 0) || (curry == 0)){
        is_found[0] = 'f';
    }
    
}

int main() {
    
    char **labyr, c, *is_found,v='n';
    int width=0, height=0, poi_arr_size = 3, row_arr_size = 3,row_arr_size_up,poi_arr_size_up;
    int xcor, ycor, i=0, j=0;
    
    is_found = &v;
    
    labyr = (char**)malloc(poi_arr_size*sizeof(char*));
    
    for(i=0;i<3;i++){
        labyr[i] = (char*) malloc(row_arr_size*sizeof(char));
    }
    
    i = 0;
    
    scanf(" %d %d ",&xcor,&ycor);
    
    /*Takes input as dynamic arrays from stdin:*/
    while((c = getchar())!= EOF){
        if(c!='\n'){
            width++;
            if(width+1 > row_arr_size){
                row_arr_size = width+1;
                labyr[i] = (char*)realloc(labyr[i],row_arr_size*sizeof(char));
            }
            labyr[i][j] = c;
            j++;
            
        }
    else{
        j=0;width=0;
        i++; height++;
        row_arr_size_up = row_arr_size-1;
        row_arr_size = 3;
        if(height+1 > poi_arr_size){
                poi_arr_size = height+1;
                labyr = (char**)realloc(labyr, poi_arr_size*sizeof(char*));
            }
        poi_arr_size_up = poi_arr_size-1;
        labyr[i] = (char*) malloc(sizeof(char)*row_arr_size);
    }
    
    }

    filler(labyr,row_arr_size_up,poi_arr_size_up,xcor,ycor,is_found);

    /*If there is at least one exit, whole cavity is filled up with stars instead of dots:*/
    
    if(is_found[0] == 'f'){
        for(i=0;i<poi_arr_size_up;i++){
            for(j=0;j<row_arr_size_up;j++){
                if(labyr[i][j] == '.'){
                    labyr[i][j] = '*';
                }
            }
        }
    }
    for(i=0;i<poi_arr_size_up;i++){
        for(j=0;j<row_arr_size_up;j++){
            printf("%c",labyr[i][j]);
        }
    printf("\n");
    }
    free(labyr);
    
    return 0;

}