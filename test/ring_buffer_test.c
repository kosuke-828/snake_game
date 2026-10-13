#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
enum{BUFFER_SIZE=6};
int field_MAX=49;
int field_MIN=-50;

struct Vec3{
    int x;
    int y;
    int z;
};

struct SNAKE
{
    int LENGTH;
    int head_index;
    int tail_index;
    struct Vec3 ring_buffer[BUFFER_SIZE];
    //struct Vec3 new_head_loc;
    struct Vec3 direction;
};
struct Vec3 food={10,44,30};

bool COMP_LOC(struct Vec3 loc_a, struct Vec3 loc_b){
    return loc_a.x == loc_b.x &&
           loc_a.y == loc_b.y &&
           loc_a.z == loc_b.z;
}

bool SELF_COLLISION(int check_num, const struct SNAKE*snake, struct Vec3 new_head_loc){
    for (int old = 0; old<check_num; old++)
    {   
        int target_index=(snake->head_index-old+BUFFER_SIZE)%BUFFER_SIZE;
        if(COMP_LOC(new_head_loc,snake->ring_buffer[target_index])){
            return true;
        }
    }
    return  false;
}

bool FIELD_COLLISION(struct Vec3 new_head_loc){
    return  new_head_loc.x>field_MAX || new_head_loc.x<field_MIN ||
            new_head_loc.y>field_MAX || new_head_loc.y<field_MIN ||
            new_head_loc.z>field_MAX || new_head_loc.z<field_MIN ;
    
}

void UPDATE_SNAKE(struct SNAKE*snake, bool will_grow){
    if(will_grow){
        snake->head_index=(snake->head_index+1)%BUFFER_SIZE;
        snake->LENGTH+=1;
        
    }
    else{
        snake->head_index=(snake->head_index+1)%BUFFER_SIZE;
        snake->tail_index=(snake->tail_index+1)%BUFFER_SIZE;        
    } 
}
void GENERATE_FOOD(const struct SNAKE*snake, struct Vec3*food){
            struct Vec3 new_food_loc;
            bool occupied;
            do{            
                new_food_loc.x=rand()%100-50;
                new_food_loc.y=rand()%100-50;
                new_food_loc.z=rand()%100-50;
                occupied=0;
                for(int i=0; i<snake->LENGTH; i++){
                    if(COMP_LOC(new_food_loc,snake->ring_buffer[(snake->head_index-i+BUFFER_SIZE)%BUFFER_SIZE]))
                        {
                        occupied=1;
                        break;
                    }
                }
            }
            while(occupied);
            *food=new_food_loc;
}

struct Vec3 CALC_NEW_HEAD_LOC(const struct SNAKE*snake){
        struct Vec3 new_head_loc;
        new_head_loc= (struct Vec3){
            snake->ring_buffer[snake->head_index].x+snake->direction.x,
            snake->ring_buffer[snake->head_index].y+snake->direction.y,
            snake->ring_buffer[snake->head_index].z+snake->direction.z};
        
        return new_head_loc;
}

int main(){    
    struct Vec3 new_head_loc;
    struct SNAKE snake={3,2,0,{{10,38,30},{10,39,30},{10,40,30},{0,0,0},{0,0,0},{0,0,0}},{0,1,0}};
    for (int i=0; i<20; i++){
        bool collision=0;
        int check_num=0;
        bool will_grow=0;
        bool generate_food=0;
        printf("snake_value \n");
        for(int j=0; j<snake.LENGTH; j++){
            printf("[%d %d %d]",
                    snake.ring_buffer[(snake.head_index-j+BUFFER_SIZE)%BUFFER_SIZE].x,
                    snake.ring_buffer[(snake.head_index-j+BUFFER_SIZE)%BUFFER_SIZE].y,
                    snake.ring_buffer[(snake.head_index-j+BUFFER_SIZE)%BUFFER_SIZE].z
                     );
        }
        printf("\n");
        printf("step %d\n\
                head_index %d   tail_index %d\n\
                snake_length %d\n\
                food_loc %d %d %d\n",
                i,
                snake.head_index, snake.tail_index,
                snake.LENGTH,
                food.x, food.y, food.z
                 );

        new_head_loc = CALC_NEW_HEAD_LOC(&snake);
        if(COMP_LOC(new_head_loc,food)&&snake.LENGTH<BUFFER_SIZE){
            will_grow=1;
            generate_food=1;
        }
        if(will_grow==0){
            check_num=snake.LENGTH-1;
        }
        else{
            check_num=snake.LENGTH;
        }
        collision=(SELF_COLLISION(check_num, &snake, new_head_loc)||FIELD_COLLISION(new_head_loc));
        if (collision==1)
        {
            break;
        }
        UPDATE_SNAKE(&snake, will_grow);
        snake.ring_buffer[snake.head_index]=new_head_loc;
        if(generate_food){
            GENERATE_FOOD(&snake, &food);
            generate_food=0;
        }
    }

}