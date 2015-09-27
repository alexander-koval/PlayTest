#pragma once

template <typename Sprite>
class SpritePool
{
using SpritePtr = boost::intrusive_ptr < Sprite > ;
public:

	SpritePool(std::size_t size, std::size_t growth);

	SpritePtr get();

	void set(SpritePtr sprite);

private:
	std::size_t m_growth;
	std::size_t m_counter;
	std::vector<SpritePtr> m_pool;
};

template <typename Sprite>
SpritePool<Sprite>::SpritePool(std::size_t size, std::size_t growth)
	: m_growth(growth)
	, m_counter(size)
	, m_pool(size)
{
	std::size_t index = size;
	while (index > 0)
	{
		m_pool[--index] = SpritePtr(new Sprite());
	}
}

template <typename Sprite>
 boost::intrusive_ptr <Sprite> SpritePool<Sprite>::get()
{
	if (m_counter > 0)
	{
		SpritePtr result = m_pool[--m_counter];
		m_pool[m_counter] = nullptr;
		return std::move(result);
	}
	std::size_t index = m_growth;
	if (index > 0) m_pool.resize(m_pool.size() + m_growth);
	while (index > 0)
	{
		m_pool[--index] = SpritePtr(new Sprite());;
	}
	m_counter = m_growth;
	return get();
}

template <typename Sprite>
void SpritePool<Sprite>::set(SpritePtr sprite)
{
	m_pool[m_counter++] = std::move(sprite);
}


