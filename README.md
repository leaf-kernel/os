# Leaf Kernel
Light as a leaf!

> [!NOTE]  
> This is a rewrite of the [original Leaf Kernel](https://github.com/leaf-kernel/kernel)

## What is Leaf?
Leaf is a Operating System Kernel written in C. The name came from the use: The kernel is as light as a leaf!

## Compatibility
|Arch|Support|Bootloader|
|----|-------|----------|
|x86-64|✔️|Limine|
|x86|❌| Leaf-Bootloader|

## Copiling
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

### Contributers
[RaphtikAtGHG](https://github.com/RaphtikAtGHG) - Updating the README
