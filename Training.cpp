#include "Training.h"

Training::Training()
{
    w_id = 0;
    e_id = 0;
}

Training::Training(int32_t w, int32_t e)
{
    w_id = w;
    e_id = e;
}

bool Training::operator==(const Workout& t) const
{
    return w_id == t.id;
}

bool Training::operator>(const Training& other) const
{
    return w_id > other.w_id;
}

bool Training::operator<(const Training& other) const
{
    return w_id < other.w_id;
}

