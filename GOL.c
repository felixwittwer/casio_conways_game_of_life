/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : GOL.c                                           */
/*                                                               */
/*   Copyright (c) 2023 Felix Wittwer                            */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include <stdio.h>

void RenderArray(int x, int y, int sizex, int sizey, int array[50][126]){
    int Ax = 0;
    int Ay = 0;

    for (Ax = 0; Ax < sizex; Ax++){
        for (Ay = 0; Ay < sizey; Ay++){
            Bdisp_SetPoint_VRAM(x + Ax, y + Ay, array[Ay][Ax]);
        }
    }
}

// 0 -> 3 Lives -> 1
// 1 -> < 2 Lives OR > 3 Lives -> 0
// 1 -> 2 Lives OR 3 Lives -> 1


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;
    int Ax = 0;
    int Ay = 0;
    int sizex = 126;
    int sizey = 50;
    int cellcount = 0;
    int generation = 0;
    int wait = 500;
    int pausegen = 0;
    int cursorx = 0;
    int cursory = 0;
    int cellsone[50][126] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    int cellstwo[50][126] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    int celltest[8][8] = {
        {0,1,1,0,0,0,1,1},
        {1,0,0,1,0,0,1,1},
        {0,1,1,0,0,0,0,0},
        {0,0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0,0},
        {0,0,1,0,0,1,0,0},
        {0,1,0,1,0,0,0,0},
        {0,0,1,1,0,0,0,0}
    };

    Bdisp_AllClr_DDVRAM();
    RenderArray(1,1, sizex, sizey, cellsone);

    while(1){
        GetKey(&key);

        RenderArray(1,1, sizex, sizey, cellsone);
        if(key==KEY_CHAR_DP && pausegen == 0){
            pausegen = 1;
            Sleep(200);
        }else if (key == KEY_CHAR_DP && pausegen ==1){
            pausegen = 0;
            Sleep(200);
        }

        if (pausegen == 1){
            if(key==KEY_CTRL_UP){
                cursory = cursory - 1;
            }else if(key==KEY_CTRL_DOWN){
                cursory = cursory + 1;
            }else if(key==KEY_CTRL_RIGHT){
                cursorx = cursorx + 1;
            }else if(key==KEY_CTRL_LEFT){
                cursorx = cursorx - 1; 
            }

            if(key==KEY_CTRL_EXE){
                if(cellsone[cursory][cursorx]==0){
                    cellsone[cursory][cursorx]=1;
                }else if(cellsone[cursory][cursorx]==1){
                    cellsone[cursory][cursorx]=0;
                }
            }

            Bdisp_AllClr_DDVRAM();
            RenderArray(1,1, sizex, sizey, cellsone);
        }

        if (pausegen == 0){
            for (Ax = 0; Ax < sizex; Ax++){
                for (Ay = 0; Ay < sizey; Ay++){
                    if (cellsone[Ay][Ax]==0){
                        cellcount = cellsone[Ay-1][Ax-1] + cellsone[Ay-1][Ax] + cellsone[Ay-1][Ax+1] +cellsone[Ay][Ax-1] + cellsone[Ay][Ax+1] + cellsone[Ay+1][Ax-1] +cellsone[Ay+1][Ax] + cellsone[Ay+1][Ax+1];

                        if (cellcount == 3){
                            cellstwo[Ay][Ax] = 1;
                        }

                    } else if (cellsone[Ay][Ax]==1){
                        cellcount = cellsone[Ay-1][Ax-1] + cellsone[Ay-1][Ax] + cellsone[Ay-1][Ax+1] +cellsone[Ay][Ax-1] + cellsone[Ay][Ax+1] + cellsone[Ay+1][Ax-1] +cellsone[Ay+1][Ax] + cellsone[Ay+1][Ax+1];

                        if(cellcount == 2 || cellcount == 3){
                            cellstwo[Ay][Ax] = 1;
                        }else if(cellcount < 2 || cellcount > 3){
                            cellstwo[Ay][Ax] = 0;
                        }
                    }
                }
            }
            

            for (Ax = 0; Ax < sizex; Ax++){
                for (Ay = 0; Ay < sizey; Ay++){
                    cellsone[Ay][Ax] = cellstwo[Ay][Ax];
                }
            }
            
            Bdisp_AllClr_DDVRAM();
            // Sleep(wait);
            RenderArray(1,1, sizex, sizey, cellstwo);
        }

    }

    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

