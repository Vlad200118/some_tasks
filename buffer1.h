#include <vector>
template <typename data_type>
class RingBufferVector
{
public:
	typedef size_t index;
	explicit RingBufferVector(size_t capacity) : capacity(capacity)
	{	
		data.reserve(capacity);
	}
	~RingBufferVector() = default;
	//Конструктор копирования
	RingBufferVector(RingBufferVector const& other)
	{
		assign(other);
	}
	//Перемещающий конструктор
	RingBufferVector(RingBufferVector const&& other) noexcept
	{
		assign(std::move_if_noexcept(other));
	}
public:

	RingBufferVector& operator = (RingBufferVector const& other)
	{
		assign(other);
		return *this;
	}

	RingBufferVector& operator = (RingBufferVector const&& other) noexcept
	{
		assign(std::move_if_noexcept(other));
		return *this;
	}

	data_type front() const //Хочу посмотреть, кто в начале очереди очереди
	{
		if (empty()) throw std::logic_error("Buffer is empty");
		return data[head];
	}
	data_type back() const //Хочу посмотреть, кто в конце очереди очереди
	{
		if (empty()) throw std::logic_error("Buffer is empty");
		return data[prev(tail)];
	}
	size_t size() const noexcept { return count; }
	bool empty()
	{
		return 0;
	}

	void push(data_type const& value) //Добавляю в конец очереди
	{
		emplace(value);
	}

	void push(data_type&& value)//Добавляю в конец очереди
	{
		emplace(std::move(value));
	}

	data_type pop()//Удаляю из головы очереди и возвращаю этот элемент
	{
		if (empty()) throw std::logic_error("Buffer is empty");
		data_type temp = std::move(data[head]);
		count--;
		data[head].~data_type();
		head = next(head);
		return temp;
	}
	bool empty() const noexcept { return count == 0; }
	bool full() const noexcept { return count == capacity; }
	void clear()//Полностью очистить буффер 
	{
		if (count == 0)
			throw std::exception("eijrwejr");
		while (count != 0)
		{
			data_type temp = pop();
		}

	}
private:
	std::vector<data_type> data;
	index head = 0;
	index tail = 0;
	size_t count = 0;
	size_t capacity = 0;

private:
	index prev(index current) const noexcept
	{
		if (current == 0)
			return capacity - 1;
		current--;
		return current;
	}

	index next(index current) const noexcept
	{
		current++;
		return (current >= capacity) ? 0 : current;
	}

	void emplace(data_type&& value)
	{
		if (full()) throw std::logic_error("Buffer is full");
		count++;
		data.push_back(value);
		tail = next(tail);
	}

	void assign(const RingBufferVector& other) noexcept
	{
		if (this == &other)
			return;
		head = other.head;
		tail = other.tail;
		count = other.count;
		capacity = other.capacity;
		for (size_t i = 0; i < capacity; i++)
		{
			data[i] = other.data[i];
		}
	}

	void assign(const RingBufferVector&& other) noexcept
	{
		if (this == &other)
			return;
		//Забираем данные у other и оставляем последний в согласованном состоянии
		head = other.head;
		tail = other.tail;
		count = other.count;
		capacity = other.capacity;
		other.head = 0;
		other.tail = 0;
		other.count = 0;
		other.capacity = 0;
		for (size_t i = 0; i < capacity; i++)
		{
			data[i] = std::move_if_noexcept(other.data[i]);
		}
	}
};