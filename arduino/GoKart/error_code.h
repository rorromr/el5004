/**
 * @brief Error code management
 * @author Rodrigo Muñoz
 * @date 2016
 *
 */

#ifndef ERROR_CODE_H
#define ERROR_CODE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Basic error definition
typedef enum {
    HW_STATUS_OK    = 0U,   ///< No error
    HW_STATUS_ERROR = 1U    ///< Error
} hw_status_type;


typedef struct __hw_status {
    uint8_t error_count;    ///< Error count
    uint8_t code;           ///< Status code
} hw_status;

/**
 * @brief Check if the status is an error
 * 
 * @param stat Status
 * @return True on error, false ptherwise
 */
bool check_error(hw_status* stat);

/**
 * @brief Set a error code
 * 
 * @param stat Status
 * @param err Error code
 */
void set_error(hw_status* stat, const uint8_t err);

#ifdef __cplusplus
}
#endif

#endif // ERROR_CODE_H