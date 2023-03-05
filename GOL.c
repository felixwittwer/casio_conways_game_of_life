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
    int cells[8][8] = {
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

    while(1){
        GetKey(&key);
        RenderArray(5,5, cells);
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

