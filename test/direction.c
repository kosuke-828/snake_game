#include<stdio.h>

struct Vec3
{
    int x;
    int y;
    int z
};

struct Vec3 direction={0,1,0};
char input;

void INITE_DIRECTION(struct Vec3*input){
    input->x=0;
    input->y=0;
    input->z=0;
}

struct Vec3 main(){
    scanf(" %c",&input);
    if(input=="w"){
        INITE_DIRECTION(&input);
        direction.y=1;
    }
    else if (input=="a")
    {  
        INITE_DIRECTION(&input);
        direction.x=1;
    }
    else if (input=="d")
    {
        INITE_DIRECTION(&input);
        direction.x=-1;
    }
    else if (input=="s")
    {
        INITE_DIRECTION(&input);
        direction.y=-1;
    }
    else if (input=="q")
    {
        INITE_DIRECTION(&input);
        direction.z=1;
    }
    else if (input=="e")
    {
        INITE_DIRECTION(&input);
        direction.z=-1;
    }
    else 
    {

    }
    printf("x,y,z %d %d %d \n",direction.x, direction.y, direction.z);
    return direction;
    
}