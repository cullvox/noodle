#pragma once

#include <string>
#include <sstream>
#include <variant>
#include <vector>
#include <filesystem>
#include <unordered_map>

namespace cullvox {

enum class noodle_type
{
    integer,
    boolean,
    floating,
    string,
    group,
};

class noodle
{
public:
    using noodle_variant = std::variant<int, bool, float, std::string>;
    using noodle_array = std::variant<std::vector<int>, std::vector<float>, std::vector<bool>, std::vector<std::string>>;

public:
    static noodle parse(const std::string& data);
    static noodle parse(const std::filesystem::path& path);

public:
    noodle() = default;
    noodle(std::string name, noodle_variant value);
    noodle(std::string name, noodle_array value);
    ~noodle() = default;

    noodle& operator=(const noodle& rhs);
    noodle& operator=(noodle_variant rhs);
    noodle& operator=(noodle_array rhs);
    noodle& operator[](const std::string& key);

    void set_name(std::string name);

    std::string name() const;
    noodle_type type() const;
    size_t size() const;
    bool is_integer() const;
    bool is_boolean() const;
    bool is_string() const;
    bool is_float() const;
    bool is_array() const;
    bool is_group() const;

    // =========== will throw if used incorrectly
    template<typename T>
    T& get();

    template<typename T>
    const T& get() const;

    template<typename T>
    T& at(int index);

    template<typename T>
    const T& at(int index);
    // ===========

    std::string to_string() const;
    std::string dump() const;

private:
    void dump_value(std::stringstream& ss) const;
    void dump_array(std::stringstream& ss) const;
    void recursive_dump(std::stringstream& ss) const;

    std::string _name;
    noodle_type _type;
    noodle_variant _value;
    bool _is_array;
    noodle_array _array;
    std::unordered_map<std::string, noodle> _children;
};

}

#include "noodle.inl"