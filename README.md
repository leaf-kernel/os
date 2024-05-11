# Leaf
Light as a leaf!

> [!NOTE]  
> If you are looking for the old repo check out [leaf-kernel/kernel-old](https://github.com/leaf-kernel/kernel-old)

## What is Leaf?
Leaf is a Operating System Kernel written in C. The name came from the use: The kernel is as light as a leaf!

## Copiling

> [!IMPORTANT]
> ### Please install the dependencies first
> * `qemu` (OPTIONAL) - For emulating the Kernel
> * `cmake` - For building the kernel
> * `xorriso` - For creating the ISO image
> * A C cross compiler and its binutils
> * `nasm` - The assembler
> You can install these on Debian based Systems using:
> ```bash
> $ sudo apt-get install qemu cmake xorriso nasm
> ```
> and on Fedora Systems:
> ```bash
> $ sudo dnf install qemu cmake xorriso nasm
> ```
> *Note:* This doesnt install the crosscompiler.

First we need to <b>configure</b> the kernel:
```bash
$ ./configure <arch>
```
> [!TIP]
> Here is an example for x86-64:
> ```bash
> $ ./configure x86_64
> ```

After that we can <b>build</b> the kernel:
```bash
$ ./build <arch>
```
> [!TIP]
> Here is an example for x86-64:
> ```bash
> $ ./build x86_64
> ```

> [!NOTE]
> ### Optionally Emulating the kernel
> You can optionally emulate the kernel using this command:
> ```bash
> $ ./run
> ```


## Other Information

<details>
  <summary>MIT License</summary>

  ### This project is licensed under the MIT License:

  MIT License

  Copyright (c) 2024 Leaf

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  
</details>
