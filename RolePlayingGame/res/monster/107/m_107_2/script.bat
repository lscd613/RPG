DIR *.*  /B >monsterAttackImage.TXT
@echo off 
set addtext=res/monster/107/m_107_0/
(for /f "delims=" %%a in (monsterAttackImage.txt) do echo %addtext%%%a)>temp.txt 
del /s/q monsterAttackImage.txt 
ren temp.txt monsterAttackImage.txt