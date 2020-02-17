cmake_minimum_required(VERSION 3.10)
project(c_coding C)

set(CMAKE_C_STANDARD 99)

add_executable(c_coding chapter2/more02.c chapter2/who1.c chapter2/cp1.c chapter2/demo.c
        chapter2/utmplib.c chapter2/c2-6.c chapter2/c2-9.c chapter3/ls1.c chapter3/filesize.c
        chapter3/ls2.c chapter3/ls3.c chapter3/c3-13.c chapter3/c3-14.c chapter3/c3-17.c chapter4/pwd1.c chapter4/c4-14.c chapter4/my_pwd.c chapter5/write1.c chapter5/showtty.c chapter5/c5-8.c chapter5/c5-22.c chapter5/my_write.c chapter6/rotate.c chapter6/play_again1.c chapter6/play_again2.c chapter6/play_again3.c chapter6/sigdemo1.c chapter6/sigdemo2.c chapter6/play_again4.c chapter7/hello1.c chapter7/hello2.c chapter7/hello4.c chapter7/hello5.c chapter7/sleep1.c chapter7/ticker_demo.c chapter7/sigdemo3.c chapter7/sigactdemo.c chapter7/bounceld.c chapter7/bounce.h chapter7/bounce2d.c chapter8/exec1.c chapter8/psh1.c chapter8/forkdemo2.c chapter8/forkdemo.c chapter8/waitdemo2.c chapter8/waitdemo1.c chapter8/psh2.c chapter8/c8-2.c chapter8/c8-5.c chapter8/c8-6.c chapter8/c8-8.c chapter8/c8-9.c chapter8/c8-10.c chapter9/smsh.h chapter9/smsh1.c chapter9/execute.c chapter9/splitline.c)