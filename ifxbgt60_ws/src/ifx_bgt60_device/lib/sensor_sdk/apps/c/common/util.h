/* ===========================================================================
** Copyright (C) 2019-2020 Infineon Technologies AG. All rights reserved.
** ===========================================================================
**
** ===========================================================================
** Infineon Technologies AG (INFINEON) is supplying this file for use
** exclusively with Infineon's sensor products. This file can be freely
** distributed within development tools and software supporting such 
** products.
** 
** THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
** OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
** INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR DIRECT, INDIRECT, 
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON 
** WHATSOEVER.
** ===========================================================================
*/
/*
 * @file util.h
 *
 * @brief This file defines the API to check if files exist and are readable.
 *
 */

#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*
==============================================================================
   1. INCLUDE FILES
==============================================================================
*/

#include <stdbool.h>
#include <stdio.h>

#include "ifxBase/Matrix.h"

/*
==============================================================================
   2. DEFINITIONS
==============================================================================
*/

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

/*
==============================================================================
   3. TYPES
==============================================================================
*/

/**
 * @brief Reads matrix from file
 *
 * Read a matrix saved by \ref print_matrix_to_file_r.
 *
 * Note that matrix needs to be valid and needs to have the right dimension.
 *
 * @param [in] f        file pointer to open file
 * @param [in] matrix   matrix
 * @retval true if successful
 * @retval false if an error occured
 */
bool get_matrix_from_file_r(FILE* f, ifx_Matrix_R_t* matrix);

/**
 * @brief Prints matrix to file
 *
 * Print matrix to the open file f. The matrix as plain text to the file, each
 * matrix on one line in row-major order.
 *
 * @param [in] f        file pointer to open file
 * @param [in] matrix   matrix that will be printed to f
 */
void print_matrix_to_file_r(FILE* f, ifx_Matrix_R_t* matrix);

/** @brief Changes to the directory name of filepath
 *
 * Given a path to a file, the function will change the current directory to
 * the directory of the file.
 *
 * Note: The function might write to filepath. However, on exit filepath will
 * be unaltered.
 *
 * @param [in]  filepath    path to file
 * @retval true if successful
 * @retval true if an error occured
 */
bool change_to_dirname(char* filepath);

/** @brief returns pointer to character string excluding path
 *
 * Used to strip path from filename
 *
 * @param [in] pathname path to file
 * @retval  pointer to character string containing filename only
 */
char* extract_filename_from_path(char* filepath);

/** @brief Checks if file is executable
 *
 * Check if the file given by pathname is both readable and executable (o+rx).
 * On Windows, this function is identical with \ref file_readable.
 *
 * @param [in] pathname path to file
 * @retval  true    if file is readable and executable
 * @retval  false   otherwise
 */
bool file_executable(const char* pathname);

/** @brief Checks if file is readable
 *
 * Check if the file given by pathname is readable.
 *
 * @param [in] pathname path to file
 * @retval  true    if file is readable
 * @retval  false   otherwise
 */
bool file_readable(const char* pathname);

/** @brief Convert uuid string to integer array
 *
 * This function accepts any uuid that has 32 hexadecimal digits [0-9a-f] and
 * will ignore any hyphens. The function checks that the uuid is in the expected
 * format and then converts it to a uint8_t array.
 *
 * @param [in] uuidString string to be checked as uuid
 * @param [out] uuid integer array containing converted uuid
 * @retval  true    if check and conversion was successful
 * @retval  false   otherwise
 */
bool get_uuid_from_string(const char* uuidString, uint8_t uuid[16]);

/** @brief Reads complete content of a file
 *
 * Read the content of the file given by pathname to a buffer and return it.
 * A null-byte is added to the read data.
 *
 * You have to free the returned pointer yourself after use.
 *
 * @param [in] pathname    path to file
 * @retval pointer to data if successful
 * @retval NULL otherwise
 */
void* file_slurp(const char* pathname);

/**
 * @brief Disables buffering to file handle
 *
 * @param [in] fh   file handle
 */
void disable_buffering(FILE* fh);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* UTIL_H */
