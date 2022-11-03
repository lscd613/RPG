DIR *.*  /B >weaponDeadImage.TXT
@echo off 
set addtext=res/weapon/w_030_2/
(for /f "delims=" %%a in (weaponDeadImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q weaponDeadImage.txt 
ren temp.txt weaponDeadImage.txt