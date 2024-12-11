/*colortext.h
a c/c++ libreary for Ubuntu/Windows for colouring output
NB: I am A newbie, so maybe some silly logics are in the code
written by Rupak Chowdhury
date: 15.09.2018
*/
#ifndef _COLORTXT_H
#define _COLORTXT_H
    #ifdef __unix__
    /*for Unix it works only if your console supports ANSI colors*/
        /*if it is included iostream 
        then it should use std::cout to print ANSI Colours*/
        #ifdef _GLIBCXX_IOSTREAM
        void TextColor(int a,int b)
        {
            std::cout<<"\x1b["<<a+30<<";"<<b+40<<"m";
        }
        void TextXY(int x,int y)
        {
            std::cout<<"\033["<<y+1<<";"<<x+1<<"H";
        }
        
        /*if code include stdio.h or cstdio
        then it should use printf() */
        #elif defined(_STDIO_H)
        void TextColor(int a,int b)
        {
            printf("\x1b[%d;%dm",30+a,40+b);
        }
        void TextXY(int x,int y)
        {
            printf("\033[%d;%dH",y+1, x+1);
        }
        #endif
        #define RESET TextColor(-29,-40)
        
        /*type of colors*/
        typedef enum  col{
        BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE,
        GRAY=60, LIGHT_RED, LIGHT_GREEN, LIGHT_YELLOW,
        LIGHT_BLUE, LIGHT_PURPLE, LIGHT_CYAN, LIGHT_WHITE,
        }Color;

        #elif defined(_WIN32)||defined(_WIN64)
        #ifndef _INC_WINDOWS 
        #include<windows.h> 
        #endif
        
        typedef enum  col{
        BLACK, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW, WHITE,
        GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_PURPLE,
         LIGHT_YELLOW, LIGHT_WHITE,
        }Color;
        
        int DefCol=7; 
        short int Time = 0;
        #define HNDLE GetStdHandle(STD_OUTPUT_HANDLE)
        #define RESET SetConsoleTextAttribute(HNDLE,DefCol)
        /*default color is that color which was applied befor 
        calling the TextColor() for the 1st time*/
        
        void TextColor(Color font,Color back)
        {
            if(!Time)
            {
                CONSOLE_SCREEN_BUFFER_INFO csbi; 	
                GetConsoleScreenBufferInfo(HNDLE,&csbi);
                DefCol=csbi.wAttributes;
                Time++;
            }
            SetConsoleTextAttribute(HNDLE,(((back)<<4)|(font)));
        }
        
        
        void TextXY(int x,int y)
        {
            COORD pos={x,y};
            SetConsoleCursorPosition(HNDLE,pos);
        }

    #endif


#endif/*_COLORTXT_H*/    
