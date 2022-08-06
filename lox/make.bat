@set FLAGS=/Wall /WX /Zi /O2 /nologo
@set SOURCES=token.cc scanner.cc main.cc
@set EXE=winlox.exe

cl %FLAGS% %SOURCES% /Fe%EXE% /EHsc /wd4668 /wd4710 /wd4711 /wd4820
