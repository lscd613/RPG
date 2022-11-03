DIR *.*  /B >roleRunImage.TXT
@echo off 
set addtext=res/102/p_102_3/
(for /f "delims=" %%a in (roleRunImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q roleRunImage.txt 
ren temp.txt roleRunImage.txt