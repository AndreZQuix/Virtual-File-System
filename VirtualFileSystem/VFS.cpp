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
				return file;
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
			activeFiles.remove(f);
		}
	}

	File* VFS::Create(const char* name)
	{
		filesystem::path userPath = filesystem::path(name);
		cout << "Trying to open or create the file in writeonly mode\n";

		list<File*>::iterator it = find_if(begin(activeFiles), end(activeFiles),
			[userPath](const File* file) { return !file->path.compare(userPath); });

		if (it != end(activeFiles))	// нашли открытый файл
		{
			if ((*it)->isReadOnly)
			{
				return *it;
			}
			else
			{
				cout << "File is already opened in readonly mode\n";
			}
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
		if (f)
		{
			if (f->isReadOnly)
			{
				f->is.seekg(0, f->is.end);
				len = f->is.tellg();
				f->is.seekg(0, f->is.beg);
				buff = new char[len];
				cout << "Reading " << len << " characters...\n";

				if (f->is.read(buff, len))	// прочитать определенное количество?
				{
					cout << "All characters read successfully\n";
				}
				else
				{
					cout << "ERROR: Only " << f->is.gcount() << " could be read\n";
				}
				return f->is.gcount();
			}
			else
			{
				cout << "File is in writeonly mode\n";
			}
		}
		else
		{
			cout << "ERROR: File can not be opened\n";
		}

		return 0;
	}

	size_t VFS::Write(File* f, char* buff, size_t len)
	{
		return 0;
	}
}