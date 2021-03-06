#pragma once
#include "IVFS.h"

namespace TestTask
{
	class VFS : public IVFS
	{
		std::list<File*> activeFiles;	// opened files storage

	public:
		File* Open(const char* name) override;
		File* Create(const char* name) override;
		size_t Read(File* f, char* buff, size_t len) override;
		size_t Write(File* f, char* buff, size_t len) override;
		void Close(File* f) override;

		~VFS()
		{
			while (!activeFiles.empty())
			{
				delete activeFiles.front();
				activeFiles.pop_front();
			}
		}
	};
}

