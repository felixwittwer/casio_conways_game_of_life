/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include <stdio.h>

void RenderArray(int x, int y, int array[8][8]){
    int Ax = 0;
    int Ay = 0;

    for (Ax = 0; Ax < 8; Ax++){
        for (Ay = 0; Ay < 8; Ay++){
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
    int cellcount = 0;
    int wait = 0;
    int pauseg = 0;
    int cellsone[8][8] = {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };

    int cellstwo[8][8] = {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
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
    RenderArray(5,5, cellsone);

    while(1){
        GetKey(&key);
        RenderArray(5,5, cellsone);
        if(key==KEY_CHAR_DP && pauseg == 0){
            pauseg = 1;
        }else if (key==KEY_CHAR_DP && pauseg ==1){
            pauseg = 0;
        }

        if (pauseg == 0){
            for (Ax = 0; Ax < 8; Ax++){
                for (Ay = 0; Ay < 8; Ay++){
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

            for (Ax = 0; Ax < 8; Ax++){
                for (Ay = 0; Ay < 8; Ay++){
                    cellsone[Ay][Ax] = cellstwo[Ay][Ax];
                }
            }
            
        }

        Sleep(wait);
        Bdisp_AllClr_DDVRAM();
        //Sleep(500);
        RenderArray(5,5, cellstwo);
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

