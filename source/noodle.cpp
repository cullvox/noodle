#include "cullvox/noodle.h"

namespace cullvox {

noodle::noodle(std::string name, noodle_variant value)
    : _name(name)
    , _type((noodle_type)value.index())
    , _value(value)
    , _is_array(false)
    , _array()
    , _children()
{
}

noodle::noodle(std::string name, noodle_array value)
    : _name(name)
    , _type((noodle_type)value.index())
    , _value()
    , _is_array(true)
    , _array(value)
    , _children()
{
}

noodle& noodle::operator=(const noodle& rhs) 
{
    _name = rhs._name;
    _type = rhs._type;
    _value = rhs._value;
    _is_array = rhs._is_array;
    _array = rhs._array;
    _children = rhs._children;

    return *this;
}

noodle& noodle::operator=(noodle_variant rhs)
{
    _type = (noodle_type)rhs.index();
    _value = rhs;
    _is_array = false;
    _array = {};
    _children = {};

    return *this;
}

noodle& noodle::operator=(noodle_array rhs)
{
    _type = (noodle_type)rhs.index();
    _value = {};
    _is_array = false;
    _array = rhs;
    _children = {};

    return *this;
}

noodle& noodle::operator[](const std::string& key)
{
    return _children[key];
}

void noodle::set_name(std::string name)
{
    _name = name;
}

std::string noodle::name() const
{
    return _name;
}

noodle_type noodle::type() const
{
    return _type;
}

size_t noodle::size() const
{
    if (is_array())      return std::visit([](auto&& arg){return arg.size();}, _array);
    else if (is_group()) return _children.size();
    else                 return 0;
}

bool noodle::is_integer() const { return _type == noodle_type::integer; }
bool noodle::is_boolean() const { return _type == noodle_type::boolean; }
bool noodle::is_string() const { return _type == noodle_type::string; }
bool noodle::is_float() const { return _type == noodle_type::floating; }
bool noodle::is_array() const { return _is_array; }
bool noodle::is_group() const { return _type == noodle_type::group; }

std::string noodle::to_string() const
{
    return "IMPLEMENT ME!";
}

std::string noodle::dump() const
{
    std::stringstream ss;
    recursive_dump(ss);
    return ss.str();
}

void noodle::dump_value(std::stringstream& ss) const
{
    switch (_type) {
    case noodle_type::integer:
    case noodle_type::floating:
    case noodle_type::boolean:
    case noodle_type::string:
        std::visit([&ss](auto&& arg){ ss << arg; }, _value);
        break;
    case noodle_type::group:
        ss << "{";
        for (const std::pair<std::string, noodle>& child : _children) {
            child.second.recursive_dump(ss);
        }
        ss << "}";
        break;
    }
}

void noodle::dump_array(std::stringstream& ss) const
{
    switch (_type) {
    case noodle_type::integer:
    case noodle_type::floating:
    case noodle_type::boolean:
    case noodle_type::string:
        std::visit([&ss](auto&& arg){ 
            for (const auto& value : arg) {
                ss << value << ",";
            }
        }, _array);
        break;
    case noodle_type::group:
        // throw std::runtime_error("Arrays of groups do not exist.");
        break;
    }
}

void noodle::recursive_dump(std::stringstream& ss) const
{
    ss << _name << "=";

    if (_is_array) dump_array(ss);
    else dump_value(ss);

    ss << ",";
}

enum class noodle_token 
{
    unexpected,
    identifier,
    integer,
    floating,
    boolean,
    string,
    left_curly,
    right_curly,
    left_bracket,
    right_bracket,
    equal,
    comma,
    end,
    newline,
};

}