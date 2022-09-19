template <typename data_type, size_t size>
class buffer_static
{
public:
	typedef size_t index;
private:
	data_type data[size];
	index head = 0; // начало очереди
	index tail = 0; //конец очереди
	size_t count = 0;//Количество элементов в очереди
public:
	explicit buffer_static() noexcept = default;
	//Конструктор копирования
	buffer_static(buffer_static const& other)
	{
		assign(other);
	}
	//Перемещающий конструктор
	buffer_static(buffer_static const&& other) noexcept
	{
		assign(std::move_if_noexcept(other));
	}
public:
	buffer_static& operator = (buffer_static const& other)
	{
		assign(other);
		return *this;
	}

	buffer_static& operator = (buffer_static const && other) noexcept
	{
		assign(std::move_if_noexcept(other));
		return *this;
	}

	size_t get_size() const noexcept { return size; }

	size_t get_count() const noexcept { return count; }

	bool full() const noexcept { return count == size; }
	bool empty() const noexcept { return count == 0; }
	void clear() noexcept
	{
		if (data == nullptr) return;

		data = nullptr;
		head = 0;
		tail = 0;
		count = 0;
	}

	void push(data_type const& value) //Добавляю в конец очереди
	{
		emplace(value);
	}

	void push(data_type && value)//Добавляю в конец очереди
	{
		emplace(std::move(value));
	}
	data_type front() //Хочу посмотреть, кто в начале очереди очереди
	{
		if (empty()) throw std::exception("Buffer is empty");
		return data[head];
	}
	data_type back() //Хочу посмотреть, кто в начале коцне очереди
	{
		if (empty()) throw std::exception("Buffer is empty");
		return data[prev(tail)];
	}

	data_type pop()//Удаляю из головы очереди
	{
		if (empty()) throw std::exception("Buffer is empty");
		data_type temp = std::move(data[head]);
		count--;
		head = next(head);
		return temp;
	}


private:
	index next(index current) const noexcept
	{
		current++;
		return (current >= size) ? 0 : current;
	}

	index prev(index current) const noexcept
	{
		if (current == 0)
		{
			return size - 1;
		}
		current--;
		return current;
	}

	void assign(const buffer_static& other) noexcept
	{
		if (this == &other)
			return;
		head = other.head;
		tail = other.tail;
		count = other.count;
		for (size_t i = 0; i < size; i++)
		{
			data[i] = other.data[i];
		}
	}

	void assign(const buffer_static&& other) noexcept
	{
		if (this == &other)
			return;
		//Забираем данные у other и оставляем последний в согласованном состоянии
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = 0;
		other.tail = 0;
		other.count = 0;
		for (size_t i = 0; i < size; i++)
		{
			data[i] = std::move_if_noexcept(other.data[i]);
		}
	}

	void emplace(data_type && value)
	{
		if (full()) throw std::exception("Buffer is full");
		count++;
		data[tail] = value;
		tail = next(tail);
	}
};
