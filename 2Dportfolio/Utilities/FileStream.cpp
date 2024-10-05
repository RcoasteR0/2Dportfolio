#include "stdafx.h"
#include "FileStream.h"

FileStream::FileStream(string path, UINT flags)
{
	isOpen = false;
	this->flags = flags;

	int iosFlags = ios::binary;
	iosFlags |= this->flags & FILE_STREAM_WRITE ? ios::out : 0;
	iosFlags |= this->flags & FILE_STREAM_READ ? ios::in : 0;

	if (this->flags & FILE_STREAM_WRITE)
	{
		out.open(path, iosFlags);
		if (out.fail())
		{
			assert(false);
			return;
		}
	}
	else if (this->flags & FILE_STREAM_READ)
	{
		in.open(path, iosFlags);
		if (in.fail())
		{
			assert(false);
			return;
		}
	}

	isOpen = true;
}

FileStream::~FileStream()
{
	Close();
}

void FileStream::Close()
{
	if (flags & FILE_STREAM_WRITE)
	{
		out.flush();
		out.close();
	}
	else if (flags & FILE_STREAM_READ)
	{
		in.clear();
		in.close();
	}
}

void FileStream::Skip(UINT n)
{
	if (flags & FILE_STREAM_WRITE)
		out.seekp(n, ios::cur);
}
