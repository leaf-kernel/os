# Leaf
Light as a leaf!

> [!NOTE]  
> If you are looking for the old repo check out [leaf-kernel/kernel-old](https://github.com/leaf-kernel/kernel-old)

## What is Leaf?
Leaf is a Operating System Kernel written in C. The name came from the use: The kernel is as light as a leaf!

## Compiling
### Dependecies
* `qemu` (OPTIONAL) - For emulating the Kernel
* `cmake` - For building the kernel
* `xorriso` - For creating the ISO image
* A C cross compiler and its binutils
* `nasm` - The assembler </br>
<br>

You can install these on Debian based Systems using:
```bash
$ sudo apt-get install qemu cmake xorriso nasm
```
and on Fedora Systems:
```bash
$ sudo dnf install qemu cmake xorriso nasm
```

### Configuring
First we need to <b>configure</b> the kernel:
```bash
$ ./configure <arch>
```

> Here is an example for x86-64:
> ```bash
> $ ./configure x86_64
> ```

After that we can <b>build</b> the kernel:
```bash
$ ./build <arch>
```
> Here is an example for x86-64:
> ```bash
> $ ./build x86_64
> ```

### Running the kernel using QEMU
You can optionally run the kernel using this command:
```bash
$ ./run <target> [qemu args...]
```


## License
Leaf is licensed under the MIT license. See [LICENSE](https://github.com/leaf-kernel/os/tree/main/LICENSE) for details.