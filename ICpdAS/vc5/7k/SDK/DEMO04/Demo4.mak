demo4.exe : demo4.obj uart.lib i7000.lib
     link -SUBSYSTEM:windows -OUT:demo4.exe demo4.obj uart.lib i7000.lib -DEFAULTLIB:user32.lib gdi32.lib winmm.lib comdlg32.lib comctl32.lib

demo4.obj : demo4.c i7000.h
     cl -c -DSTRICT -G3 -Ow -W3 -Zp -Tp demo4.c
