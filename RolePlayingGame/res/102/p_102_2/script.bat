DIR *.*  /B >roleDeadImage.TXT
@echo off 
set addtext=res/102/p_102_2/
(for /f "delims=" %%a in (roleDeadImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q roleDeadImage.txt 
ren temp.txt roleDeadImage.txt