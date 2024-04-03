
namespace cullvox {

template<typename T>
T& noodle::get()
{
    return std::get<T>(_value);
}

template<typename T>
const T& noodle::get() const
{
    return std::get<T>(_value);
}

template<typename T>
T& noodle::at(int index)
{
    return std::get<T>(_array)[index];
}

template<typename T>
const T& noodle::at(int index)
{
    return std::get<T>(_array)[index];
}

} // namespace cullvox