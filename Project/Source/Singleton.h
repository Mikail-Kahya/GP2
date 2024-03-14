#pragma once

template <typename SingletonType>
class Singleton
{
public:
	~Singleton() = default;

	Singleton(const Singleton& other)					= delete;
	Singleton(Singleton&& other) noexcept				= delete;
	Singleton& operator=(const Singleton& other)		= delete;
	Singleton& operator=(Singleton&& other) noexcept	= delete;

	static SingletonType& Get()
	{
		static SingletonType instance{};
		return instance;
	}

protected:
	Singleton() = default;
};