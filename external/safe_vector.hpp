#pragma once

template<typename T>
class safe_vector
{
private:
	std::vector<T> vector_ = {};

	// capacity
public:
	void clear()
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		vector_.clear();
		std::atomic_thread_fence(std::memory_order_release);
	}

	bool empty()
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		return vector_.empty();
		std::atomic_thread_fence(std::memory_order_release);
	}

	size_t size() const
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		return vector_.size();
		std::atomic_thread_fence(std::memory_order_release);
	}

	// modifiers
public:
	void push_back(const T& value)
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		vector_.push_back(value);
		std::atomic_thread_fence(std::memory_order_release);
	}

	void pop_back()
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		vector_.pop_back();
		std::atomic_thread_fence(std::memory_order_release);
	}

	void swap(std::vector<T>& x)
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		vector_.swap(x);
		std::atomic_thread_fence(std::memory_order_release);
	}

	std::vector<T> copy()
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		return vector_;
		std::atomic_thread_fence(std::memory_order_release);
	}

	T& operator[](size_t index)
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		return vector_[index];
		std::atomic_thread_fence(std::memory_order_release);
	}

	const T& operator[](size_t index) const
	{
		std::atomic_thread_fence(std::memory_order_acquire);
		return vector_[index];
		std::atomic_thread_fence(std::memory_order_release);
	}
};