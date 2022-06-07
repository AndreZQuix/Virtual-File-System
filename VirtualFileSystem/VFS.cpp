#include "VFS.h"
#include <iostream>

namespace TestTask
{
	File* VFS::Open(const char* name)
	{
		std::cout << "Trying to open the file in readonly mode\n";

		std::list<File*>::iterator it = std::find_if(begin(activeFiles), end(activeFiles), 
			[name](const File* file) { return !(strcmp(file->path, name)); });

		if (it == end(activeFiles))	// такого открытого файла не найдено
		{
			File* file = new File(true);
			file->is.open(name, std::ifstream::binary | std::ifstream::in);

			if (file->is.is_open())
			{
				activeFiles.push_back(file);

				file->is.seekg(0, file->is.end);
				file->length = file->is.tellg();
				file->is.seekg(0, file->is.beg);
				file->buffer = new char[file->length];
				std::cout << "Reading " << file->length << " characters...\n";

				for (const auto& f : activeFiles)	// DEBUGGING
				{
					std::cout << f->path << std::endl;
					std::cout << f->isReadOnly << std::endl;
				}

				if (file->is.read(file->buffer, file->length))
				{
					std::cout << "All characters read successfully\n";
					return file;
				}
				else
				{
					std::cout << "Error: Only " << file->is.gcount() << " could be read\n";
				}
			}

			Close(file);
		}
		else if ((*it)->isReadOnly)	// файл уже открыт в readonly
		{
			return *it;
		}

		std::cout << "Can not open the file in readonly mode\n";
		return nullptr;
	}

	void VFS::Close(File* f)
	{
		if (f)
		{
			f->is.close();
			f->os.close();
			delete f;
		}
	}

	File* VFS::Create(const char* name)
	{
		std::cout << "Trying to open or create the file in writeonly mode\n";

		std::list<File*>::iterator file = std::find_if(begin(activeFiles), end(activeFiles),
			[name](const File* file) { return !strcmp(file->path, name); });

		if (file != end(activeFiles))	// нашли файл
		{
			// не должен быть открыт. Если файл уже открыт, его надо обрабатывать
		}
		else
		{
			File* file = new File(false);
			file->os.open(name, std::ofstream::out);
			if (file->os.is_open())
			{
				std::cout << "File has been created in writeonly mode\n";
				strcpy_s(file->path, name);
				activeFiles.push_back(file);
				return file;
			}
			Close(file);
			delete file;
		}

		std::cout << "Can not open or create the file in writeonly mode\n";
		return nullptr;
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