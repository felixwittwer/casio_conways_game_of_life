@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.

if exist debug\*.obj  del debug\*.obj
if exist GOL.G1A  del GOL.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\Program Files\CASIO\fx-9860G SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\Program Files\CASIO\fx-9860G SDK\Tools\MakeAddinHeader363.exe" "C:\Users\Felix\Desktop\casio_conways_game_of_life\casio_conways_game_of_life-main"
if not exist GOL.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

