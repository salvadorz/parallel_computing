/**
 * @file utility.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for utility
 *
 */

#ifndef UTILITY_H_
#define UTILITY_H_

// Includes
#include <CL/cl.hpp>

#define EPSILON (1e-2f)

/**
 * @brief Print platform info
 * 
 * @param PlatformList vector of platforms
 */
void print_platform_info(std::vector<cl::Platform> *PlatformList);
/**
 * @brief Get the platform id with string object
 * 
 * @param name 
 * @return uint 
 */
uint get_platform_id_with_string(std::vector<cl::Platform> *, const char *name);
/**
 * @brief Print device info
 * 
 * @param DeviceList objects of devices
 */
void print_device_info(std::vector<cl::Device> *DeviceList);
/**
 * @brief Assigns random number from LO to HI to all location of X and Y
 * 
 * @param X @param Y and @param Z are the arrays to fill
 * @param LO @param HI are the min and max values range
 * @param vectorSize size of arrays
 */
void fill_generate(cl_float X[], cl_float Y[], cl_float Z[], float LO, float HI, size_t vectorSize);
/**
 * @brief Verification of the results
 * 
 * @param X @param Y and @param Z are the arrays to fill
 * @param CalcZ is the array with the results
 * @param vectorSize size of arrays
 * @return true if the results are correct, false otherwise
 */
bool verification(float X[], float Y[], float Z[], float CalcZ[], size_t vectorSize);
/**
 * @brief Check error
 * 
 * @param err 
 * @param name 
 */
void checkErr(cl_int err, const char *name);

#endif /* UTILITY_H_ */