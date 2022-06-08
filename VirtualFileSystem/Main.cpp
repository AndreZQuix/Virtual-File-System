#include "VFS.h"
#include <string>

int main()
{
    _CrtMemState _ms;       // memory leak
    _CrtMemCheckpoint(&_ms);

    TestTask::IVFS* VFS = new TestTask::VFS();      // тестирование

    /*std::string path("G:/VS/VirtualFileSystem/Test.txt");*/

    std::cout << "\nOpening first file..." << std::endl;
    TestTask::File* firstFile = VFS->Open("G:/VS/VirtualFileSystem/Test.txt");

    std::cout << "\nPath: " << firstFile->path << std::endl;

    std::cout << "\nCreating second file..." << std::endl;
    TestTask::File* secondFile = VFS->Create("G:/VS/TEST/Test2.txt");

    std::cout << "\nOpening second file..." << std::endl;
    secondFile = VFS->Open("G:/VS/TEST/Test2.txt");

    std::cout << "\nClosing second file..." << std::endl;
    VFS->Close(secondFile);

    std::cout << "\nOpening second file..." << std::endl;
    secondFile = VFS->Open("G:/VS/TEST/Test2.txt");
    
    std::cout << "\nReading first file..." << std::endl;
    size_t len = 30;
    char* buff = new char[len];
    size_t readBytes = VFS->Read(firstFile, buff, len);
    std::cout << "\nBytes read: " << readBytes << std::endl;
    std::cout << buff;

    std::cout << "\nClosing first file..." << std::endl;
    VFS->Close(firstFile);

    std::cout << "\nCreating first file..." << std::endl;
    firstFile = VFS->Create("G:/VS/VirtualFileSystem/Test.txt");

    std::cout << "\n\nWriting to the first file..." << std::endl;
    size_t writtenBytes = VFS->Write(firstFile, buff, strlen(buff));
    std::cout << "Bytes written: " << writtenBytes << std::endl;

    delete[] buff;
    delete VFS;

    _CrtMemDumpAllObjectsSince(&_ms);
    return 0;
}

