#pragma once

#include "MemoryMappedFile.h"

class FMessageReceiver
{
protected:
	FMemoryMappedFile m_memoryMappedFile;
	uint8* m_memoryMap;
	TUniquePtr<uint8_t[]> m_messages;
	uint32 m_offset = 0;
	uint32 m_length = 0;
#if UE_BUILD_SHIPPING == 0
	TArray<const char*> m_types;
#endif

public:
	FMessageReceiver();
	~FMessageReceiver();

	bool hasNext() const;
	uint8_t getId() const;

	template <typename T>
	const T& getMessage();

	void receiveMessages();
};

#include "MessageReceiver.inl"
