DIR *.*  /B >roleAttackImage.TXT
@echo off 
set addtext=res/102/p_102_0/
(for /f "delims=" %%a in (roleAttackImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q roleAttackImage.txt 
ren temp.txt roleAttackImage.txt