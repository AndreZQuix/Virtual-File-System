#pragma once
#include "IVFS.h"
#include <list>

namespace TestTask
{
	class VFS : public IVFS
	{
		std::list<File*> activeFiles;

	public:
		File* Open(const char* name);
		File* Create(const char* name);
		size_t Read(File* f, char* buff, size_t len);
		size_t Write(File* f, char* buff, size_t len);
		void Close(File* f);

		~VFS()
		{
			while (!activeFiles.empty())
			{
				delete activeFiles.front();
				activeFiles.pop_front();
			}

			std::cout << "Object has been destroyed" << std::endl;
		}
	};
}

