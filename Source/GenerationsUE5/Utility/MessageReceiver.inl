template<typename T, typename = void>
struct has_data_size : std::false_type {};

template<typename T>
struct has_data_size<T, std::void_t<decltype(T::dataSize)>> : std::true_type {};

template <typename T>
const T& FMessageReceiver::getMessage()
{
	const T* message = reinterpret_cast<const T*>(m_messages.Get() + m_offset);
	check(((reinterpret_cast<size_t>(message) & (alignof(T) - 1)) == 0) && message->id == T::s_id);

	if constexpr (has_data_size<T>::value)
		m_offset += offsetof(T, data) + message->dataSize;

	else
		m_offset += sizeof(T);

#if UE_BUILD_SHIPPING == 0
	m_types.Push(typeid(T).name() + 7);
#endif

	return *message;
}