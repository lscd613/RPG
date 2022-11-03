DIR *.*  /B >weaponRunImage.TXT
@echo off 
set addtext=res/weapon/w_030_3/
(for /f "delims=" %%a in (weaponRunImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q weaponRunImage.txt 
ren temp.txt weaponRunImage.txt