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

    // read array an set pixels on VRAM
    for (Ax = 0; Ax < sizex; Ax++){
        for (Ay = 0; Ay < sizey; Ay++){
            Bdisp_SetPoint_VRAM(x + Ax, y + Ay, array[Ay][Ax]);
        }
    }
}

// print int variables to screen
void printminiInt(int x, int y, int f){
    unsigned char buffer[9];
    sprintf(buffer, "%d", f);
    PrintMini(x,y, buffer, MINI_OVER);
}


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

    Bdisp_AllClr_DDVRAM();
    RenderArray(1,1, sizex, sizey, cellsone); // write cellsone to VRAM

    while(1){
        GetKey(&key);

        RenderArray(1,1, sizex, sizey, cellsone);
        // handle pause/play of simulation
        if((key==KEY_CHAR_DP||key==KEY_CTRL_F1) && pausegen == 0){
            pausegen = 1;
            Sleep(200);
        }else if ((key==KEY_CHAR_DP||key==KEY_CTRL_F1) && pausegen == 1){
            pausegen = 0;
            Sleep(200);
        }else if (key==KEY_CTRL_F2){
            // set all positions in both arrays to 0
            for (Ax = 0; Ax < sizex; Ax++){
                for (Ay = 0; Ay < sizey; Ay++){
                    cellsone[Ay][Ax] = 0;
                    cellstwo[Ay][Ax] = 0;
                }
            }
            // update other variables
            generation = 0;
            pausegen = 1;
        }

        if (pausegen == 1){
            // handle cursor movement
            if(key==KEY_CTRL_UP){
                cursory = cursory - 1;
            }else if(key==KEY_CTRL_DOWN){
                cursory = cursory + 1;
            }else if(key==KEY_CTRL_RIGHT){
                cursorx = cursorx + 1;
            }else if(key==KEY_CTRL_LEFT){
                cursorx = cursorx - 1; 
            }

            // manipulate single pixel on cursor position
            if(key==KEY_CTRL_EXE){
                if(cellsone[cursory][cursorx]==0){
                    cellsone[cursory][cursorx]=1;
                }else if(cellsone[cursory][cursorx]==1){
                    cellsone[cursory][cursorx]=0;
                }
            }

            Bdisp_AllClr_DDVRAM();
            RenderArray(1,1, sizex, sizey, cellsone); // write cellsone to VRAM
        }

        // 0 -> 3 Lives -> 1
        // 1 -> < 2 Lives OR > 3 Lives -> 0
        // 1 -> 2 Lives OR 3 Lives -> 1

        // apply CGOL rules when simulation is not paused
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
            
            // transfer cellstwo to cellsone for next generation
            for (Ax = 0; Ax < sizex; Ax++){
                for (Ay = 0; Ay < sizey; Ay++){
                    cellsone[Ay][Ax] = cellstwo[Ay][Ax];
                }
            }
            
            Bdisp_AllClr_DDVRAM();
            // Sleep(wait);
            RenderArray(1,1, sizex, sizey, cellstwo); // write array to VRAM
            generation = generation + 1; // update generation variable
        }

        if(pausegen == 1){
            locate(2,8);
            Print("\xE6\x9E");  // play indocator
        }else if(pausegen == 0){
            Bdisp_DrawLineVRAM(8, 57, 8, 61);
            Bdisp_DrawLineVRAM(10, 57, 10, 61); // pause indicator
        }

        Bdisp_DrawLineVRAM(1,54,19,54);
        Bdisp_DrawLineVRAM(19,54,19,62); // first menu box for play/pause indicator

        Bdisp_DrawLineVRAM(21,54,39,54);
        Bdisp_DrawLineVRAM(39,54,39,62); // second menu box for DEL
        PrintMini(25,57,"DEL", MINI_OVER);
        PrintMini(43,57,"Gen:", MINI_OVER);

        printminiInt(63,57,generation); // display current number of generations on screen
        
        Bdisp_PutDisp_DD(); // load VRAM to DD (display driver)


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

