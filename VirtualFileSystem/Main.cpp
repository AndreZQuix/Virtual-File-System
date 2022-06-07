#include <iostream>
#include "VFS.h"
#include <string>

int main()
{
    TestTask::IVFS* VFS = new TestTask::VFS();

    std::string path("G:/VS/VirtualFileSystem/Test.txt");

    std::cout << "\nOpening first file..." << std::endl;
    TestTask::File* firstFile = VFS->Open(path.c_str());

    std::cout << "\nCreating second file..." << std::endl;
    TestTask::File* secondFile = VFS->Create("G:/VS/TEST/Test2.txt");

    std::cout << "\nOpening second file..." << std::endl;
    secondFile = VFS->Open("G:/VS/VirtualFileSystem/Test2.txt");

    std::cout << "\nClosing first file..." << std::endl;
    VFS->Close(firstFile);
}

