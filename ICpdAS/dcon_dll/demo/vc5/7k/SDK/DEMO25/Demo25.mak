demo25.exe : demo25.obj uart.lib i7000.lib
     link -SUBSYSTEM:windows -OUT:demo25.exe demo25.obj uart.lib i7000.lib -DEFAULTLIB:user32.lib gdi32.lib winmm.lib comdlg32.lib comctl32.lib

demo25.obj : demo25.c i7000.h
     cl -c -DSTRICT -G3 -Ow -W3 -Zp -Tp demo25.c
