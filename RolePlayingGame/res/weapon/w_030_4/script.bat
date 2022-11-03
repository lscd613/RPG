DIR *.*  /B >weaponStayImage.TXT
@echo off 
set addtext=res/weapon/w_030_4/
(for /f "delims=" %%a in (weaponStayImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q weaponStayImage.txt 
ren temp.txt weaponStayImage.txt