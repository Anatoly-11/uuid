@echo off
copy headers\uuid.h      test
copy x64\Debug\uuid.lib  test
copy x64\Debug\uuid.dll  test\x64\Debug

copy headers\uuid.h     ..\rnd\headers
copy x64\Debug\uuid.lib ..\rnd\lib

copy headers\uuid.h     ..\rnd\test\headers
copy x64\Debug\uuid.lib ..\rnd\test\lib
copy x64\Debug\uuid.dll ..\rnd\test\x64\Debug

copy headers\uuid.h     ..\matrix\headers
copy x64\Debug\uuid.lib ..\matrix\lib
copy x64\Debug\uuid.dll ..\matrix\x64\Debug