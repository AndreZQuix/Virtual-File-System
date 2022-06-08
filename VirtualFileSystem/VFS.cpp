#include "VFS.h"

using namespace std;

namespace TestTask
{
	File* VFS::Open(const char* name)
	{
		filesystem::path userPath = filesystem::path(name);
		cout << "Trying to open the file in READONLY mode...\n";

		list<File*>::iterator it = find_if(begin(activeFiles), end(activeFiles),
			[userPath](const File* file) { return !file->path.compare(userPath); });	// поиск необходимого файла среди открытых

		if (it == end(activeFiles))	// такого открытого файла не найдено
		{
			File* file = new File(true);
			file->is.open(name, ifstream::binary | ifstream::in);

			if (file->is.is_open())
			{
				activeFiles.push_back(file);
				return file;
			}

			cout << "ERROR: File can not be opened in READONLY mode\n";
			Close(file);
		}
		else if ((*it)->isReadOnly)	// файл уже открыт в readonly
		{
			cout << "File is already opened in READONLY mode\n";
			return *it;
		}

		cout << "ERROR: File is already opened in WRITEONLY mode\n";
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
		else
		{
			cout << "ERROR: File can not be closed\n";
		}
	}

	File* VFS::Create(const char* name)
	{
		filesystem::path userPath = filesystem::path(name);
		cout << "Trying to open or create the file in WRITEONLY mode\n";

		list<File*>::iterator it = find_if(begin(activeFiles), end(activeFiles),
			[userPath](const File* file) { return !file->path.compare(userPath); });

		if (it != end(activeFiles))	// открытый файл найден
		{
			if ((*it)->isReadOnly)
			{
				cout << "File is already opened in READONLY mode\n";
				return *it;
			}
			else
			{
				cout << "File is already opened in WRITEONLY mode\n";
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
			file->os.open(userPath, ofstream::binary | ofstream::out | ofstream::app);
			if (file->os.is_open())
			{
				cout << "File has been created or opened in WRITEONLY mode\n";
				file->path = userPath;
				activeFiles.push_back(file);
				return file;
			}
			Close(file);
		}

		cout << "ERROR: File can not be created or opened in WRITEONLY mode\n";
		return nullptr;
	}

	size_t VFS::Read(File* f, char* buff, size_t len)
	{
		if (f)
		{
			if (f->isReadOnly)
			{
				f->is.seekg(0, f->is.end);
				size_t fileLength = f->is.tellg();
				f->is.seekg(0, f->is.beg);
				cout << "Reading " << fileLength << " characters...\n";

				if (f->is.read(buff, fileLength))
				{
					cout << "All characters were read successfully\n";
				}
				else
				{
					cout << "ERROR: Only " << f->is.gcount() << " could be read\n";
				}
				return f->is.gcount();
			}
			else
			{
				cout << "ERROR: File is already opened in WRITEONLY mode\n";
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
		if (f)
		{
			if (!f->isReadOnly)
			{
				// запись в файл
			}
			else
			{
				cout << "ERROR: File is already opened in READONLY mode\n";
			}
		}
		else
		{
			cout << "ERROR: File can not be opened\n";
		}
		return 0;
	}
}