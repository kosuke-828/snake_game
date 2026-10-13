#include<stdio.h>

struct Vec3
{
    int x;
    int y;
    int z
};

struct Vec3 direction={0,1,0};
char input;

void INPUT_DIRECTION(struct Vec3*input){
    

}

struct Vec3 main(){
    scanf(" %c",&input);
    if(input=="w"){
        direction.y={0,1,0}
    }
    else if (input=="a")
    {
        direction={1,0,0};
    }
    else if (input=="d")
    {
        direction={-1,0,0};
    }
    
    

}