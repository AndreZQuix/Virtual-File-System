﻿#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>

namespace TestTask
{
	struct File
	{
		bool isReadOnly;
		std::ifstream is;
		std::ofstream os;
		std::filesystem::path path;

		File(const bool isReadOnly) : isReadOnly(isReadOnly), is(std::ifstream()), os(std::ofstream()), path(std::filesystem::path()) {};
	};

	struct IVFS
	{
		virtual File* Open(const char* name) = 0; // Открыть файл в readonly режиме. Если нет такого файла или же он открыт во writeonly режиме - вернуть nullptr
		virtual File* Create(const char* name) = 0; // Открыть или создать файл в writeonly режиме. Если нужно, то создать все нужные поддиректории, упомянутые в пути. Вернуть nullptr, если этот файл уже открыт в readonly режиме.
		virtual size_t Read(File* f, char* buff, size_t len) = 0; // Прочитать данные из файла. Возвращаемое значение - сколько реально байт удалось прочитать
		virtual size_t Write(File* f, char* buff, size_t len) = 0; // Записать данные в файл. Возвращаемое значение - сколько реально байт удалось записать
		virtual void Close(File* f) = 0; // Закрыть файл

		virtual ~IVFS() = default;
	};
}