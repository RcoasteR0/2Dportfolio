#pragma once

enum EFileStream : UINT
{
	FILE_STREAM_READ = 1U << 0,
	FILE_STREAM_WRITE = 1U << 1,
	FILE_STREAM_APPEND = 1U << 2,
};

class FileStream
{
public:
	FileStream(string path, UINT flags);
	~FileStream();

	void Close();
	void Skip(UINT n);

	template <typename T>
	void Write(T value)
	{
		out.write(reinterpret_cast<const char*>(&value), sizeof(T));
	}

	template <>
	void Write(string value)
	{
		Write(value.size());
		out.write(value.c_str(), value.size());
	}

	template <typename T>
	void Read(T& value)
	{
		in.read(reinterpret_cast<char*>(&value), sizeof(T));
	}

	template <>
	void Read(string& value)
	{
		UINT temp = Read<UINT>();
		value.assign(temp, 'a');
		in.read(const_cast<char*>(value.c_str()), temp);
	}

	template <typename T>
	T Read()
	{
		T value;
		Read(value);

		return value;
	}

private:
	ofstream out;
	ifstream in;

	UINT flags = 0;
	bool isOpen = false;
};