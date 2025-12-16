==38202== Memcheck, a memory error detector
==38202== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==38202== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==38202== Command: ./cubed 1
==38202== 
==38202== Syscall param writev(vector[0]) points to uninitialised byte(s)
==38202==    at 0x4BCB894: writev (writev.c:26)
==38202==    by 0x4CC2ACA: ??? (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==38202==    by 0x4CC2C4E: ??? (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==38202==    by 0x4CC3D7E: xcb_writev (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==38202==    by 0x48A90B8: _XSend (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==38202==    by 0x48AE148: _XReadEvents (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==38202==    by 0x48AE52B: XWindowEvent (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==38202==    by 0x1145D5: mlx_int_wait_first_expose (in /home/mehras/cub3d/cubed)
==38202==    by 0x114305: mlx_new_window (in /home/mehras/cub3d/cubed)
==38202==    by 0x112C28: init_mlx (main.c:800)
==38202==    by 0x112F83: execute (main.c:828)
==38202==    by 0x10FC1C: main (main.c:884)
==38202==  Address 0x4f4846c is 28 bytes inside a block of size 16,384 alloc'd
==38202==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38202==    by 0x489842D: XOpenDisplay (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==38202==    by 0x1140B6: mlx_init (in /home/mehras/cub3d/cubed)
==38202==    by 0x112BCA: init_mlx (main.c:792)
==38202==    by 0x112F83: execute (main.c:828)
==38202==    by 0x10FC1C: main (main.c:884)
==38202== 
==38202== 
==38202== HEAP SUMMARY:
==38202==     in use at exit: 2,188,936 bytes in 913 blocks
==38202==   total heap usage: 12,751 allocs, 11,838 frees, 3,437,472 bytes allocated
==38202== 
==38202== LEAK SUMMARY:
==38202==    definitely lost: 0 bytes in 0 blocks
==38202==    indirectly lost: 0 bytes in 0 blocks
==38202==      possibly lost: 0 bytes in 0 blocks
==38202==    still reachable: 2,188,936 bytes in 913 blocks
==38202==         suppressed: 0 bytes in 0 blocks
==38202== Rerun with --leak-check=full to see details of leaked memory
==38202== 
==38202== Use --track-origins=yes to see where uninitialised values come from
==38202== For lists of detected and suppressed errors, rerun with: -s
==38202== ERROR SUMMARY: 3 errors from 1 contexts (suppressed: 0 from 0)
