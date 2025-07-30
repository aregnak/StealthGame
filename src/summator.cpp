#include "summator.h"

#include <godot_cpp/core/class_db.hpp>

void Summator::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("add, value"), &Summator::add);
    godot::ClassDB::bind_method(godot::D_METHOD("reset"), &Summator::reset);
    godot::ClassDB::bind_method(godot::D_METHOD("get_total"), &Summator::getTotal);
}

void Summator::add(int p_value) { count += p_value; }
void Summator::reset() { count = 0; }
int Summator::getTotal() const { return count; }

Summator::Summator()
    : count(0)
{
}