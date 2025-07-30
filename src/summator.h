#pragma once

#include <godot_cpp/classes/object.hpp>

class Summator : public godot::Object
{
    GDCLASS(Summator, godot::Object)

    int count;

protected:
    static void _bind_methods();

public:
    void add(int p_value);
    void reset();
    int getTotal() const;

    Summator();
};