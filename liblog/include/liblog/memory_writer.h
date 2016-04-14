#include <cassert>
#include <string>
#include <iterator>

namespace liblog
{
	namespace details
	{
#ifdef _SECURE_SCL
		// Use checked iterator to avoid warnings on MSVC.
		template <typename T>
		inline stdext::checked_array_iterator<T*> make_ptr(T *ptr, std::size_t size)
		{
			return stdext::checked_array_iterator<T*>(ptr, size);
		}
#else
		template <typename T>
		inline T *make_ptr(T *ptr, std::size_t) { return ptr; }
#endif

		const size_t INLINE_BUFFER_SIZE = 500;

		template <typename T>
		class Buffer {
		private:
			Buffer(const Buffer&) = delete;
			Buffer& operator=(const Buffer&) = delete;

		protected:
			T *ptr_;
			std::size_t size_;
			std::size_t capacity_;

			Buffer(T *ptr = 0, std::size_t capacity = 0)
				: ptr_(ptr), size_(0), capacity_(capacity) {}

			virtual void grow(std::size_t size) = 0;

		public:
			virtual ~Buffer() {}

			std::size_t size() const { return size_; }

			std::size_t capacity() const { return capacity_; }

			void resize(std::size_t new_size)
			{
				if (new_size > capacity_)
				{
					grow(new_size);
				}
				size_ = new_size;
			}

			void reserve(std::size_t capacity)
			{
				if (capacity > capacity_)
				{
					grow(capacity);
				}	
			}

			void clear() noexcept { size_ = 0; }

			void push_back(const T &value)
			{
				if (size_ == capacity_)
				{
					grow(size_ + 1);
				}
				ptr_[size_++] = value;
			}

			template <typename U>
			void append(const U *begin, const U *end)
			{
				auto append_size = end - begin;
				assert(append_size >= 0);
				//static_cast<typename std::make_unsigned<typename decltype(append_size)>::type()
				std::size_t new_size = size_ + append_size;
				
				if (new_size > capacity_)
				{
					grow(new_size);
				}
				std::uninitialized_copy(begin, end, details::make_ptr(ptr_, capacity_) + size_);
				size_ = new_size;
			}

			T &operator[](std::size_t index) { return ptr_[index]; }
			const T &operator[](std::size_t index) const { return ptr_[index]; }
		};

		template <typename T, std::size_t SIZE, typename Allocator = std::allocator<T> >
		class MemoryBuffer : private Allocator, public Buffer<T> {
		private:
			T data_[SIZE];

			void deallocate()
			{
				if (this->ptr_ != data_)
				{
					Allocator::deallocate(this->ptr_, this->capacity_);
				}
			}

		protected:
			void grow(std::size_t size)
			{
				std::size_t new_capacity = this->capacity_ + this->capacity_ / 2;
				if (size > new_capacity)
				{
					new_capacity = size;
				}
				T *new_ptr = this->allocate(new_capacity);
				// The following code doesn't throw, so the raw pointer above doesn't leak.
				std::uninitialized_copy(this->ptr_, this->ptr_ + this->size_, details::make_ptr(new_ptr, new_capacity));
				std::size_t old_capacity = this->capacity_;
				T *old_ptr = this->ptr_;
				this->capacity_ = new_capacity;
				this->ptr_ = new_ptr;
				// deallocate may throw (at least in principle), but it doesn't matter since
				// the buffer already uses the new storage and will deallocate it in case
				// of exception.
				if (old_ptr != data_)
				{
					Allocator::deallocate(old_ptr, old_capacity);
				}
			}

		public:
			explicit MemoryBuffer(const Allocator &alloc = Allocator())
				: Allocator(alloc), Buffer<T>(data_, SIZE)
			{}

			~MemoryBuffer() { deallocate(); }

		public:

			Allocator get_allocator() const { return *this; }
		};

		template <typename Char>
		class BasicWriter {
		private:
			Buffer<Char>& buffer_;

			BasicWriter(const BasicWriter&) = delete;
			BasicWriter& operator=(const BasicWriter&) = delete;

			Char* grow_buffer(std::size_t n)
			{
				std::size_t size = buffer_.size();
				buffer_.resize(size + n);
				return details::make_ptr(&buffer_[size], n);
			}

			void write(const std::basic_string<Char>& str)
			{
				buffer_.append(str.data(), str.data() + str.size());
			}
		protected:
			explicit BasicWriter(Buffer<Char> &b) : buffer_(b) {}

		public:
			virtual ~BasicWriter() {}

			std::size_t size() const { return buffer_.size(); }

			const Char* data() const noexcept { return &buffer_[0]; }

			std::basic_string<Char> str() const
			{
				return std::basic_string<Char>(&buffer_[0], buffer_.size());
			}

			BasicWriter &operator<<(int value)
			{
				write(std::to_string(value));
				return *this;
			}
			BasicWriter &operator<<(unsigned value)
			{
				write(std::to_string(value));
				return *this;
			}
			BasicWriter &operator<<(long value)
			{
				write(std::to_string(value));
				return *this;
			}
			BasicWriter &operator<<(unsigned long value)
			{
				write(std::to_string(value));
				return *this;
			}
			BasicWriter &operator<<(long long value)
			{
				write(std::to_string(value));
				return *this;
			}

			BasicWriter &operator<<(unsigned long long value)
			{
				write(std::to_string(value));
				return *this;
			}

			BasicWriter &operator<<(double value)
			{
				write(std::to_string(value));
				return *this;
			}

			BasicWriter &operator<<(long double value)
			{
				write(std::to_string(value));
				return *this;
			}

			BasicWriter &operator<<(char value)
			{
				buffer_.push_back(value);
				return *this;
			}

			BasicWriter &operator<<(const std::basic_string<Char> value)
			{
				write(value);
				return *this;
			}

			void clear() noexcept { buffer_.clear(); }
		};

		template <typename Char, typename Allocator = std::allocator<Char> >
		class BasicMemoryWriter : public BasicWriter<Char> {
		private:
			details::MemoryBuffer<Char, details::INLINE_BUFFER_SIZE, Allocator> buffer_;

		public:
			explicit BasicMemoryWriter(const Allocator& alloc = Allocator())
				: BasicWriter<Char>(buffer_), buffer_(alloc) {}

			BasicMemoryWriter(BasicMemoryWriter &&other)
				: BasicWriter<Char>(buffer_), buffer_(std::move(other.buffer_)) {
			}

			BasicMemoryWriter &operator=(BasicMemoryWriter &&other) {
				buffer_ = std::move(other.buffer_);
				return *this;
			}
		};

		typedef BasicMemoryWriter<char> MemoryWriter;
	}
}