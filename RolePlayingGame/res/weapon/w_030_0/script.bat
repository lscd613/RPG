DIR *.*  /B >weaponAttackImage.TXT
@echo off 
set addtext=res/weapon/w_030_0/
(for /f "delims=" %%a in (weaponAttackImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q weaponAttackImage.txt 
ren temp.txt weaponAttackImage.txt