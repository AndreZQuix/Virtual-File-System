#include "VFS.h"
#include <iostream>

namespace TestTask
{
	File* VFS::Open(const char* name)
	{
		std::cout << "Trying to open the file in readonly mode\n";

		std::list<File*>::iterator file = std::find_if(begin(files), end(files), 
			[name](const File* file) { return !(strcmp(file->path, name) && file->isOpened); });

		if (file != end(files))
		{
			(*file)->is.open(name, std::ifstream::binary | std::ifstream::in);

			if ((*file)->is.is_open())
			{
				(*file)->is.seekg(0, (*file)->is.end);
				(*file)->length = (*file)->is.tellg();
				(*file)->is.seekg(0, (*file)->is.beg);
				(*file)->buffer = new char[(*file)->length];
				std::cout << "Reading " << (*file)->length << " characters...\n";

				(*file)->isOpened = true;

				for (const auto& f : files)	// DEBUGGING
				{
					std::cout << f->path << std::endl;
					std::cout << f->isOpened << std::endl;
					std::cout << f->isReadOnly << std::endl;
				}

				if ((*file)->is.read((*file)->buffer, (*file)->length))
				{
					std::cout << "All characters read successfully\n";
					return (*file);
				}
				else
				{
					std::cout << "Error: Only " << (*file)->is.gcount() << " could be read\n";
				}
			}

			Close(*file);
		}

		std::cout << "File can not be opened\n";
		return nullptr;
	}

	void VFS::Close(File* f)
	{
		if (f)
		{
			f->is.close();
			f->os.close();
			f->isOpened = false;
		}
	}

	File* VFS::Create(const char* name)
	{
		File* file = new File(true);
		file->os.open(name, std::fstream::out);
		if (file->os.is_open())
		{
			strcpy_s(file->path, name);
			files.push_back(file);
			return file;
		}

		return nullptr;

	//	std::cout << "Trying to open the file in writeonly mode\n";

	//	std::list<File*>::iterator it = std::find_if(begin(files), end(files),
	//		[name](const File* file) { return !strcmp(file->path, name); });

	//	if (it == end(files))
	//	{
	//		// создать файл
	//	}
	//	else if(!(*it)->isOpened)
	//	{
	//		
	//	}
	//	
	//	std::cout << "File can not be opened or created\n";
		//return nullptr;
	}

	size_t VFS::Read(File* f, char* buff, size_t len)
	{
		return 0;
	}

	size_t VFS::Write(File* f, char* buff, size_t len)
	{
		return 0;
	}
}