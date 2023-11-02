@echo off
del /q distr\*.*
copy headers\uuid.h  distr
copy x64\Debug\uuid.dll  distr
copy x64\Debug\uuid.lib  distr

copy distr\uuid.h ..\testUUID\headers
copy distr\uuid.lib ..\testUUID\lib
copy distr\uuid.dll ..\testUUID\x64\Debug

copy distr\uuid.h ..\rnd\headers
copy distr\uuid.lib ..\rnd\lib

copy distr\uuid.h ..\matrix\headers
copy distr\uuid.lib ..\matrix\lib
copy distr\uuid.dll ..\matrix\x64\Debug