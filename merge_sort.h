

template <class Type, typename RandomAccessIterator>
void merge(Type& temp, RandomAccessIterator first_left, RandomAccessIterator last_left, RandomAccessIterator first_right, RandomAccessIterator last_right)
{
	size_t i = 0;
	while (first_left <= last_left and first_right <= last_right)
	{
		if (*first_left <= *first_right)
		{
			temp[i++] = *first_left;
			first_left++;
		}
		else
		{
			temp[i++] = *first_right;
			first_right++;			}
	}
	while (first_left <= last_left)
	{
		temp[i++] = *first_left;
		first_left++;
	}
	while (first_right <= last_right)
	{
		temp[i++] = *first_right;
		first_right++;
	}
}

template <typename RandomAccessIterator>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	typedef RandomAccessIterator iterator;
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;

	size_t const length = std::distance(first, last);
	if (length > 1)
	{
		value_type* temp = new value_type[length];
		iterator first_left, last_left, first_right, last_right;

		for (size_t BlockSizeIterator = 1; BlockSizeIterator < length; BlockSizeIterator *= 2)
		{
			for (size_t BlockIterator = 0; BlockIterator < length - BlockSizeIterator; BlockIterator += 2 * BlockSizeIterator)
			{
				first_left = first + BlockIterator;
				last_left = first + BlockIterator + BlockSizeIterator - 1;
				first_right = first + BlockIterator + BlockSizeIterator;
				if ((BlockIterator + 2 * BlockSizeIterator - 1) < length)
					last_right = first + BlockIterator + 2 * BlockSizeIterator - 1;
				else
					last_right = last - 1;

				if (first_left >= last) break;

				merge(temp, first_left, last_left, first_right, last_right);

				size_t length2 = std::distance(first_left, last_right) + 1;
				for (size_t MergeIterator = 0; MergeIterator < length2; MergeIterator++)
				{
					*(first_left + MergeIterator) = temp[MergeIterator];
				}
			}
		}
		delete [] temp;
	}
}