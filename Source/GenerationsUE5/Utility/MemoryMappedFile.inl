inline FMemoryMappedFile::FMemoryMappedFile()
{
#ifdef _WIN64
	m_handle = OpenFileMapping(
		FILE_MAP_READ,
		FALSE,
		s_name);

	static_assert(sizeof(size_t) == 8);
#else
	m_handle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		nullptr,
		PAGE_READWRITE,
		0,
		s_size,
		s_name);

	static_assert(sizeof(size_t) == 4);
#endif
	check(m_handle != nullptr);
}

inline FMemoryMappedFile::~FMemoryMappedFile()
{
	check(!m_mapped);
	const BOOL result = CloseHandle(m_handle);
	check(result == TRUE);
}

inline void* FMemoryMappedFile::map() const
{
	check(!m_mapped);

	void* result = MapViewOfFile(
		m_handle,
#ifdef _WIN64
		FILE_MAP_READ,
#else
		FILE_MAP_WRITE,
#endif
		0,
		0,
		0);

	check(result != nullptr);

#if UE_BUILD_SHIPPING == 0
	m_mapped = true;
#endif
	return result;
}

inline void FMemoryMappedFile::flush(void* buffer, size_t size) const
{
	const BOOL result = FlushViewOfFile(buffer, size);
	check(result == TRUE);
}

inline void FMemoryMappedFile::unmap(void* buffer) const
{
	check(m_mapped);
	const BOOL result = UnmapViewOfFile(buffer);
	check(result == TRUE);
#if UE_BUILD_SHIPPING == 0
	m_mapped = false;
#endif
}