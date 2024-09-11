#include "MessageReceiver.h"

FMessageReceiver::FMessageReceiver()
{
	m_memoryMap = static_cast<uint8_t*>(m_memoryMappedFile.map());
	m_messages = MakeUnique<uint8_t[]>(FMemoryMappedFile::s_size);
}

FMessageReceiver::~FMessageReceiver()
{
	m_memoryMappedFile.unmap(m_memoryMap);
}

bool FMessageReceiver::hasNext() const
{
	return m_offset < m_length;
}

uint8_t FMessageReceiver::getId() const
{
	return m_messages[m_offset];
}

void FMessageReceiver::receiveMessages()
{
	m_offset = sizeof(uint32_t);
	m_length = *reinterpret_cast<uint32_t*>(m_memoryMap);
	memcpy(m_messages.Get(), m_memoryMap, m_length);

#if UE_BUILD_SHIPPING == 0
	m_types.Empty();
#endif
}
