#cutils

**cutils** is a set of very simple but powerful tools to make one's life a
little easier while one is programming in C. I created the tools mostly for
use in my personal projects, however I hope/believe many will find it just as
useful as I do.

for more info visit: [www.cutils.org](http://www.cutils.org)

- - -
###**cenv** : Environment Generator

Sets up a minimal C environment. It is very practical to test ideas and short
snippets quicly, or to start a new project from scratch. The generated
`makefile` is very extensible and maintainable.

*Usage:*

    $ python3 cenv.py <dirname> <filename>
    $ cd <dirname>
    $ make
    $ ./build/<filename>


- - -
###**cref** : Quick Reference

An up-to-date reference to standard C library. It has two purposes:

  1. To be a quick reference guide, with short explanations
  2. To use it in a text editor to extend the auto complition's functionality

*THIS FILE IS **NOT A VALID C FILE**, DON'T COMPILE NOR INCLUDE IT!*

*(The only reason it has `.c` extension, is to make it easier for text editors
to set the proper syntax highlighter automatically to this file.)*


- - -
###**ccol** : Colors Helper

A single header-only set of color related tools: base type aliases, conversion
and mixing functions, name constants and IO.


- - -
###**cbug** : Tiny Debugger

A very lightweight debugging/logging single header-only utility, contains only
3 function-like macros which are printing to the standard error output:

  1. `debug()`

    Increases it's own counter and prints out the location informations from
    where it was called.

  2. `debugs(str)`

    Does the same as `debug()` plus extends the output with a single
    `char*` string.

  3. `debugf(fmt, ...)`

    Does the same as `debug()` plus extends the output with a formatted `char*`
    string. It works the same way as the `stdio`'s `printf` function does.

**Example Output:**

    <counter> File: '<file name>.c', line: <line number>, function: '<function name>'
        <Custom message if debugs() or debugf() has been used>

    000 File: 'main.c', line: 39, function: 'main'
        "I'm a debugging message!"

It can be turned off by defining an empty `CBUG_OFF` macro variable before the
include macro statement. If it is defined all the apperences of the functions
will be removed from the source file.

Another great usecase of this header is to extend the **`cexc`** utility, when
the handling mode of that is set to logging. This can be seen in the next
example:

    #include <stdio.h>  // stderr

    #define CEXC_LOG

    #include "cexc.h"   // (start|stop)_exception_handling(), raise()
    #include "cbug.h"   // debug()

    void func(void *ptr)
    {
        if (ptr != NULL)
            return;
        debug();
        raise("Pointer is NULL", 16);
    }

    int main(void)
    {
        start_exception_handling(stderr);

        func(NULL);

        stop_exception_handling();
        return 0;
    }

And the output is:

    000 File: 'main.c', line: 13, function: 'func'
    EXCEPTION: Pointer is NULL


- - -
###**cfps** : Frame Per Second Helper

A single header-only frame per second counter. It implements two inline
functions, which are:

  1. `printfps(timer_func)`:

    It requires a timer function as it's only argument which returns a double
    value. It prints the frame per second value to the standard output stream.

  2. `getfps(timer_func, handler_func, data_ptr)`:

    It is a more general purpose fps function. It also requires a timer function
    which returns a double value, but it also requires a handler function, which
    will be called on every second; and a pointer to any kind of data, which
    will be passed to the handler function, to deal with it.

The next example shows how to use `getfps` with GLFW to set the title of the
window to show the actual frame per second value:

    #include <stdio.h>       // snprintf()
    #include <GLFW/glfw3.h>  // glfw*(), GLFW*
    #include "cfps.h"        // getfps()


    static void fps_title_setter(int fps, void *data)
    {
        void **array = (void **)data;
        char *buffer = (char *)(array[1]);
        snprintf(buffer, *((int *)(array[2])), "[FPS: %d]", fps);
        glfwSetWindowTitle((GLFWwindow *)(array[0]), buffer);
    }


    // ... GLFW setup


    void run(GLFWwindow *window)
    {
        char fps_title_txt[10];
        int  fps_title_len = 10;
        void *data[] = {window, fps_title_txt, &fps_title_len};

        glfwSwapInterval(0)
        while (!glfwWindowShouldClose(window))
        {
            // ... Draw something

            glfwSwapBuffers(window)
            glfwPollEvents();

            getfps(glfwGetTime, fps_title_setter, &data);
        }
    }


- - -
###**cexc** : Exception Handling System

A single header-only exception handling system. It is very useful to track all
malfunctions in the codebase which are not terminating the program, but makes it
harder to debug the code and find out what went wrong.

It implements the following nine functions:

  1. `start_exception_handling(file_ptr)`

    Creates a global exception handler object, which can be accessed by the
    following functions from any file, as long as `cexc.h` is included. It only
    requires a `FILE` pointer, where all the exceptions will be written to. This
    function has to be called only once (preferably at the beginning of the
    program) or after a previous exception handler object was deleted
    successfully by the `stop_exception_handling()` function. *(In that case,
    all the data stored in the exception handler object will be deleted, so for
    example the custom handlers has to be passed again.)*

  2. `stop_exception_handling()`

    Destroys the previously created exception handler object.

  3. `raise(msg, len)`

    Uploads a `const char *` exception message to the exception handler object's
    buffer. If another `raise` function will be called before the message
    received by a `catch` function, the buffer will be overwritten and the
    previous message will be lost.

  4. `catch()`

    Writes the exception message from the exception handler object's buffer to
    the file pointer defined at the exception handler object's initialisation.
    After it successfully writes the message, it sets the buffer to contain the
    default `NO ERROR` message.

  5. `set_exception_handling_pointer(ptr)`

    Stores a user defined custom pointer in the exception handling object. By
    default the pointer set to `NULL`. This pointer will be passed to both
    custom handler functions during the call of `craise` and `ccatch`.

  6. `set_exception_handling_custom_raise(func)`

    Stores a user defined function's pointer in the exception handler object.
    This function will be called by the `craise` function, and the user pointer
    will be passed as argument. By default an "empty" function is stored. The
    function prototype is `(void)(*)(void*)`.

  7. `set_exception_handling_custom_catch(func)`

    Stores a user defined function's pointer in the exception handler object.
    This function will be called by the `ccatch` function, and the user pointer
    will be passed as argument. By default an "empty" function is stored. The
    function prototype is `(void)(*)(void*)`.

  8. `craise(msg, len)`

    Acts exactly as the `raise` function, plus it calls the user defined custom
    raise function and passing the user defined pointer as argument to that.

  9. `ccatch()`

    Acts exactly as the `catch` function, plus it calls the user defined custom
    catch function and passing the user defined pointer as argument to that.

When the exception object's buffer cannot be realloc'd *(it happens when the
current buffer size is smaller than the new exception message it supposed to
store, and the memory reallocation fails)* the `INTERNAL` exception message will
be stored in the buffer, indicating the error.

The whole exception handling system can be removed from the source by defining
the `CEXC_OFF` macro variable before the `cexc.h` included. The bahaviour of the
exception handling system can be set to "logging-mode", which means, the `catch`
functions will be removed, and the `raise` function will write the exception
messages right when it's called directly to the file pointer defined at the
exception handler object's initialisation. This can be achieved by defining a
`CEXC_LOG` macro variable before the `cexc.h` included.

The next example demonstrates the usage of the custom handler functions. It
extends the standard handler functions with a simple counter functionality:

    #include <stdio.h>    // fprintf()
    #include "cexc.h"

    static void
    custom_raise(void *counter)
    {
        (*(int *)counter)++;
    }


    static void
    custom_catch(void *counter)
    {
        fprintf(stderr, "COUNTER: %d\n", *(int *)counter);
    }


    int main(void)
    {
        start_exception_handling(stderr);

        int error_counter = 0;
        set_exception_handling_pointer(&error_counter);
        set_exception_handling_custom_raise(custom_raise);
        set_exception_handling_custom_catch(custom_catch);

        ccatch();
    #define msg "Custom catcher and raiser functions!"
        craise(msg, sizeof(msg));
    #undef msg
        ccatch();
        ccatch();

        stop_exception_handling();
        return 0;
    }

And the output is:

    EXCEPTION: NO ERROR
    COUNTER: 0
    EXCEPTION: Custom catcher and raiser functions!
    COUNTER: 1
    EXCEPTION: NO ERROR
    COUNTER: 2

- - -
Copyright (C) 2014 Peter Varo

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.