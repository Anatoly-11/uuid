@echo off
copy headers\uuid.h      ..\testUUID\headers
copy x64\Debug\uuid.lib  ..\testUUID\lib
copy x64\Debug\uuid.dll  ..\testUUID\x64\Debug

copy headers\uuid.h ..\rnd\headers
copy x64\Debug\uuid.lib ..\rnd\lib

copy headers\uuid.h     ..\matrix\headers
copy x64\Debug\uuid.lib ..\matrix\lib
copy x64\Debug\uuid.dll ..\matrix\x64\Debug