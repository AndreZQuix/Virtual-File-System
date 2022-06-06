#pragma once
#include "IVFS.h"
#include <list>

namespace TestTask
{
	class VFS : public IVFS
	{
		std::list<File*> files;

	public:
		File* Open(const char* name);
		File* Create(const char* name);
		size_t Read(File* f, char* buff, size_t len);
		size_t Write(File* f, char* buff, size_t len);
		void Close(File* f);
	};
}
