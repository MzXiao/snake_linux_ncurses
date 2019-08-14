//#include <curses.h>

//#define MULTI_THREAD 1

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>
#ifdef MULTI_THREAD
#include <pthread.h>

#endif


// #define StartX 0 /* 决定游标初始位置 */
// #define StartY 0

// int x = StartX; /* 宣告 x,y 并设定其初值 */
// int y = StartY;

typedef struct point
{
    /* data */
    int x;
    int y;
    struct point *next;
}PointList;

typedef struct 
{
    int length;
    int direction; //1 up 2 right 3down 4left
    int xpos;//no use
    int ypos;//no use
    PointList *body;
}Snake;



void initial(void );
void endprogram(void);
void* CheckInput(void * snake);
void NoBlockCheck();
int Snake_Move_Body(Snake *ss);
void Snake_Show(Snake *ss);

void Creat_Random_Fruit();
void Fruit_Show();
int Hit_Fruit(int x,int y);
int Hit_Body(int x,int y);


Snake *ss;

PointList *fruit;

void initSnake()
{
    ss=(Snake *)malloc(sizeof(Snake));
    ss->length=2;
    ss->direction=2;
    ss->xpos=COLS/2;
    ss->ypos=LINES/2;

    PointList* snakebody=(PointList *)malloc(sizeof(PointList));
    snakebody->x=3;
    snakebody->y=3;
    PointList* second =(PointList *)malloc(sizeof(PointList));
    second->x=2;
    second->y=3;
    second->next=NULL;
    snakebody->next =second;

    ss->body=snakebody;
}

int Snake_Move_Body(Snake *ss)
{
    int direction =ss->direction;
    PointList *head =ss->body;
    PointList *newPoint=(PointList *)malloc(sizeof(PointList));
    int xnew;
    int ynew;
    if(direction==1)
    {
            xnew=(head->x)%COLS;
            ynew=(head->y-1+LINES)%LINES;
    }
    else if(direction==2)
    {
            xnew=(head->x+1)%COLS;
            ynew=(head->y)%LINES;
    }
    else if(direction==3)
    {
            xnew=(head->x)%COLS;
            ynew=(head->y+1)%LINES;
    }
    else if(direction==4)
    {
            xnew=(head->x-1+COLS)%COLS;
            ynew=(head->y)%LINES;
    }
    if(Hit_Body(xnew,ynew)==1)
    {
        
        //endprogram();
        //exit(0);
        return -1;
    }
        ss->body=newPoint;
        newPoint->next=head;
        newPoint->x=xnew;
        newPoint->y=ynew;
    if(Hit_Fruit(xnew,ynew)==1)
    {
        return 1;
    }
    
    
    PointList *secondtail =ss->body;
    
    while(secondtail->next->next!=NULL)
        {     
            secondtail=secondtail->next;
        }
        
    

    secondtail->next=NULL;

    return 0;
        // int xchange_m1=head->x-1;
        //int xchange_p1=head->x+1;
        // int ychange_m1=head->y-1;
        //int ychange_p1=head->y+1;
        // xchange_m1=xchange_m1%COLS;
        // ychange_m1=ychange_m1%LINES;

        //xchange_p1=xchange_p1%COLS;
        //ychange_p1=ychange_p1%LINES;


        // if(xchange_m1<0)
        // {
        //     xchange_m1+=COLS;
        // }
        // if(ychange_m1<0)
        // {
        //     ychange_m1+=LINES;
        // }   
}

void Snake_Show(Snake *ss)
{
    clear();
    PointList *p=ss->body;
    while(p!=NULL)
    {   
        
        mvaddch(p->y,p->x,'o');
        if(p==ss->body)
        {
            mvaddch(p->y,p->x,'H');
        }
        if(p->next==NULL)
        {
            mvaddch(p->y,p->x,'T');
        }
        p=p->next;
    }
    Fruit_Show();
    refresh();
}

void Fruit_Show()
{
    //clear();
    PointList *p=fruit->next;
    while(p!=NULL)
    {
        mvaddch(p->y,p->x,ACS_DIAMOND);
        p=p->next;
    }
     //refresh();
}

void Creat_Random_Fruit()
{
    fruit =(PointList *)malloc(sizeof(PointList));
    PointList *tail=fruit;
    
    int i,j=0;
    srand(time(NULL));
    for(int i=0;i<10;i++)
    {
        PointList *newfruit =(PointList *)malloc(sizeof(PointList));
        newfruit->x=rand()%COLS;
        newfruit->y=rand()%LINES;
        newfruit->next=NULL;
        
        tail->next=newfruit;
        tail=newfruit;       
    }
}
int Hit_Fruit(int x,int y)
{
    PointList *p=fruit->next;
    while(p!=NULL)
    {
        if(p->x==x &&p->y ==y)
        {
            ss->length++;
            p->x=rand()%COLS;
            p->y=rand()%LINES;
            return 1;
        }
        p=p->next;
    }
    return 0;
}

int Hit_Body(int x,int y)
{
    PointList *p=ss->body;
    while(p!=NULL)
    {
        if(p->x==x &&p->y ==y)
        {
            //exit(0);
            return 1;
        }
        p=p->next;
    }
    return 0;
}




int main(int argc, char const *argv[])
{
    /* code */

    //system("./shells/setsize.sh");

    //printf("hello world\n");
    initial();
    //beep();
    //echochar('h');
    initSnake();

    Creat_Random_Fruit();
    //Fruit_Show();

    //box(stdscr, '|', '-'); /* 画方框 */
    //move(ss->ypos,ss->xpos);
    #ifdef MULTI_THREAD
    pthread_t id;
    pthread_create(&id,NULL,(void *)CheckInput,(void *)ss);
    #endif
    
    int flag=0;
    while (1)
    {
        /* code */
        // x++;
        // y=y%LINES;
        // x=x%COLS;
        // if(x<0)
        // {
        //     x+=COLS;
        // }
        // if(y<0)
        // {
        //     y+=LINES;
        // }
        // echochar(50);
        // move(y, x);

        // clear();
        // switch(ss->direction)
        // {
        //     case 1:
        //         ss->ypos--;
        //         break;
        //     case 2:
        //         ss->xpos++;
        //         break;
        //     case 3:
        //         ss->ypos++;
        //         break;
        //     case 4:
        //         ss->xpos--;
        //         break;
        // }
        // ss->xpos=ss->xpos%COLS;
        // ss->ypos=ss->ypos%LINES;
        // if(ss->xpos<0)
        // {
        //     ss->xpos+=COLS;
        // }
        // if(ss->ypos<0)
        // {
        //     ss->ypos+=LINES;
        // }   
        
        // mvaddch(ss->ypos,ss->xpos,'o');
        // refresh();
        //sleep(1);


        //NoBlockCheck();
        flag=Snake_Move_Body(ss);
        Snake_Show(ss);
        #ifdef MULTI_THREAD
        if(flag<0) 
        {
            pthread_cancel(id);
            pthread_join(id,NULL);
            break;
        }
        usleep(1000*100);//50ms
        #else
        if(flag<0)
        {
            break;
        }
        NoBlockCheck();
        #endif

    }
    endprogram();
       
    return 0;
}



void initial() 
{ 
    initscr(); //初始化
    cbreak(); //
    nonl();
    raw(); 
    noecho();
    //echo(); 
    intrflush(stdscr,FALSE); 
    keypad(stdscr,TRUE); 
    curs_set(0);//hide curser
    timeout(100);//non blocking 
    refresh(); 
} 


void endprogram()
{   
    //char result[80];
    //sprintf(result,"Your Snake Length %d !",ss->length);
    mvaddstr(LINES-3,COLS/2-1,"GAME OVER");
    //mvaddstr(LINES-2,COLS/2,result);
    mvprintw(LINES-2,0,"Your Snake Length %d !",ss->length);
    mvaddstr(LINES-1, 0, "Press any key to quit");
    timeout(-1);
    refresh();
    getch();
    endwin();
}


void* CheckInput(void * snake)
{

    Snake *ss=(Snake *)snake;

    int ch;
    while(1)
    {
        ch = getch();
        switch (ch)
        {

        case KEY_UP:
            if(ss->direction!=3)
            {
                ss->direction=1;
            }
            break;

        case KEY_DOWN:
            if(ss->direction!=1)
            {
                ss->direction=3;
            } 
            break;

        case KEY_RIGHT:
            if(ss->direction!=4)
            {
                ss->direction=2;
            }
            break;

        case KEY_LEFT:
            if(ss->direction!=2)
            {
                ss->direction=4;
            }
            break;
        case '\r': /* 判断是否 ENTER 键被按下 */
            
            break;

        case 27/* constant-expression */:
            /* code */

            endprogram();            
            exit(0);
            break;
        
        default:                  
            break;

        }
  
        //refresh();refresh();
    }
    

}

void NoBlockCheck()
{
    int ch;
    ch=getch();
    switch (ch)
        {

        case KEY_UP:
            if(ss->direction!=3)
            {
                ss->direction=1;
            }
            break;

        case KEY_DOWN:
            if(ss->direction!=1)
            {
                ss->direction=3;
            } 
            break;

        case KEY_RIGHT:
            if(ss->direction!=4)
            {
                ss->direction=2;
            }
            break;

        case KEY_LEFT:
            if(ss->direction!=2)
            {
                ss->direction=4;
            }
            break;
        case '\r': /* 判断是否 ENTER 键被按下 */
            break;

        case 27/* constant-expression ESC*/:
            /* code */
            // endprogram(); 
            // exit(0);
            break;
        
        default:                  
            break;

        }
}

