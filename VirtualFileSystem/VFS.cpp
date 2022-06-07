#include "VFS.h"

using namespace std;

namespace TestTask
{
	File* VFS::Open(const char* name)
	{
		filesystem::path userPath = filesystem::path(name);
		cout << "Trying to open the file in readonly mode\n";

		list<File*>::iterator it = find_if(begin(activeFiles), end(activeFiles), 
			[userPath](const File* file) { return !file->path.compare(userPath); });

		if (it == end(activeFiles))	// такого открытого файла не найдено
		{
			File* file = new File(true);
			file->is.open(name, ifstream::binary | ifstream::in);

			if (file->is.is_open())
			{
				activeFiles.push_back(file);

				file->is.seekg(0, file->is.end);
				file->length = file->is.tellg();
				file->is.seekg(0, file->is.beg);
				file->buffer = new char[file->length];
				cout << "Reading " << file->length << " characters...\n";

				for (const auto& f : activeFiles)	// DEBUGGING
				{
					cout << f->path << endl;
					cout << f->isReadOnly << endl;
				}

				if (file->is.read(file->buffer, file->length))
				{
					cout << "All characters read successfully\n";
					return file;
				}
				else
				{
					cout << "Error: Only " << file->is.gcount() << " could be read\n";
				}
			}

			Close(file);
		}
		else if ((*it)->isReadOnly)	// файл уже открыт в readonly
		{
			return *it;
		}

		cout << "Can not open the file in readonly mode\n";
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
		filesystem::path userPath = filesystem::path(name);
		cout << "Trying to open or create the file in writeonly mode\n";

		list<File*>::iterator file = find_if(begin(activeFiles), end(activeFiles),
			[userPath](const File* file) { return !file->path.compare(userPath); });

		if (file != end(activeFiles))	// нашли открытый файл
		{

		}
		else
		{
			try
			{
				filesystem::create_directories(userPath.parent_path());
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}

			File* file = new File(false);
			file->os.open(userPath, ofstream::out);
			if (file->os.is_open())
			{
				cout << "File has been created in writeonly mode\n";
				file->path = userPath;
				activeFiles.push_back(file);
				return file;
			}
			Close(file);
		}

		cout << "Can not open or create the file in writeonly mode\n";
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