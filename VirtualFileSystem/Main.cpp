#include <iostream>
#include "VFS.h"
#include <string>

int main()
{
    TestTask::IVFS* VFS = new TestTask::VFS();

    std::string path("G:/VS/VirtualFileSystem/Test.txt");

    TestTask::File* file = VFS->Open(path.c_str());
    TestTask::File* secondFile = VFS->Create("G:/VS/VirtualFileSystem/Test2.txt");
    secondFile = VFS->Open("G:/VS/VirtualFileSystem/Test2.txt");
    VFS->Close(file);
    //TestTask::File* seCfile = VFS->Open(path.c_str());
}

