# VirtualFileSystem

A virtual file system (VFS) is programming that forms an interface between an operating system's kernel and a more concrete file system. The VFS serves as an abstraction layer that gives applications access to different types of file systems and local and network storage devices.

This is a simple VFS without GUI that includes the following features:
1. Open file in readonly mode.
2. Create or open file in writeonly mode.
3. Read file (only in readonly mode).
4. Write file (only in writeonly mode).
If file is already opened, system returns it to the user. If there is a need to open a file in writeonly mode, but this file does not exist, system creates it.

Memory leak tested with CRT library.
