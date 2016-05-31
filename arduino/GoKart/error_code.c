#include "error_code.h"

bool check_error(hw_status* stat)
{
    return stat->code & HW_STATUS_ERROR; // Check bit
}

void set_error(hw_status* stat, const uint8_t err)
{
    ++stat->error_count; // Increment error count
    stat->code = err; // Set error code
}
