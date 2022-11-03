DIR *.*  /B >monsterRunImage.TXT
@echo off 
set addtext=res/monster/107/m_107_3/
(for /f "delims=" %%a in (monsterRunImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q monsterRunImage.txt 
ren temp.txt monsterRunImage.txt