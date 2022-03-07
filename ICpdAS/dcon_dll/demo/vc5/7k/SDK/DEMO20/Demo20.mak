demo20.exe : demo20.obj uart.lib i7000.lib
     link -SUBSYSTEM:windows -OUT:demo20.exe demo20.obj uart.lib i7000.lib -DEFAULTLIB:user32.lib gdi32.lib winmm.lib comdlg32.lib comctl32.lib

demo20.obj : demo20.c i7000.h
     cl -c -DSTRICT -G3 -Ow -W3 -Zp -Tp demo20.c
