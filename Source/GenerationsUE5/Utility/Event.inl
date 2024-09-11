inline FGensEvent::FGensEvent(LPCTSTR name, BOOL initialState)
{
	m_handle = CreateEvent(
		nullptr,
		TRUE,
		initialState,
		name);

	check(m_handle != nullptr);
}

inline FGensEvent::FGensEvent(LPCTSTR name)
{
	m_handle = OpenEvent(
		EVENT_ALL_ACCESS,
		FALSE,
		name);

	check(m_handle != nullptr);
}

inline FGensEvent::~FGensEvent()
{
	CloseHandle(m_handle);
}

inline void FGensEvent::wait() const
{
	const DWORD result = WaitForSingleObject(m_handle, INFINITE);
	check(result == WAIT_OBJECT_0);
}

inline bool FGensEvent::waitImm() const
{
	const DWORD result = WaitForSingleObject(m_handle, 1u);
	return result == WAIT_OBJECT_0;
}

inline void FGensEvent::set() const
{
	const BOOL result = SetEvent(m_handle);
	check(result == TRUE);
}

inline void FGensEvent::reset() const
{
	const BOOL result = ResetEvent(m_handle);
	check(result == TRUE);
}
