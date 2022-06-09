#include "VFS.h"
#include <string>

int main()
{
    TestTask::IVFS* VFS = new TestTask::VFS();      // тестирование

    std::filesystem::path path = std::filesystem::current_path().parent_path();

    std::cout << "Opening first file..." << std::endl;
    std::filesystem::path path1 = path / std::filesystem::path("Test.txt");
    TestTask::File* file1 = VFS->Open(path1.string().c_str());

    if(file1)
        std::cout << "\nPath: " << file1->path << std::endl;

    std::cout << "\nCreating second file..." << std::endl;
    std::filesystem::path path2 = path / std::filesystem::path("/TEST") / std::filesystem::path("Test2.txt");
    TestTask::File* file2 = VFS->Create(path2.string().c_str());

    std::cout << "\nOpening second file..." << std::endl;
    file2 = VFS->Open(path1.string().c_str());

    std::cout << "\nClosing second file..." << std::endl;
    VFS->Close(file2);

    std::cout << "\nOpening second file..." << std::endl;
    file2 = VFS->Open(path1.string().c_str());
    
    std::cout << "\nReading first file..." << std::endl;
    size_t len = 30;
    char* buff = new char[len];
    size_t readBytes = VFS->Read(file1, buff, len);
    std::cout << "\nBytes read: " << readBytes << std::endl;
    std::cout << buff;

    std::cout << "\nClosing first file..." << std::endl;
    VFS->Close(file1);

    std::cout << "\nCreating first file..." << std::endl;
    file1 = VFS->Create(path1.string().c_str());

    std::cout << "\n\nWriting to the first file..." << std::endl;
    size_t writtenBytes = VFS->Write(file1, buff, strlen(buff));
    std::cout << "Bytes written: " << writtenBytes << std::endl;

    delete[] buff;
    delete VFS;

    return 0;
}

