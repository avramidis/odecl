#ifndef SODECL_OPENLC_MGR_HPP
#define SODECL_OPENLC_MGR_HPP

#include "sodecl.hpp"

namespace sodecl
{

/**
 * @brief Class that implements the OpenCL functions needed by the ODE and SDE solvers.
 * 
 */
class opencl_mgr
{
  private:
    /********************************************************************************************
	* OPENCL HARDWARE SECTION VARIABLES
	*/

    cl_uint m_opencl_platform_count;                        /**< Number of OpenCL platforms */
    std::vector<sodecl::platform *> m_opencl_platforms;     /**< Vector which stores the sodecl::platform objects. One object for each OpenCL platform */
    cl_uint m_selected_opencl_platform;                     /**< The index of the selected sodecl::platform object in the m_platforms vector */
    cl_uint m_selected_opencl_device;                       /**< The index of the selected sodecl::device object in m_devices vector of selected platform */
    device_Type m_selected_opencl_device_type;              /**< Selected OpenCL device type */

  public:
    /**
     * @brief Default constructor.
     * 
     */
    opencl_mgr(){};

    /**
     * @brief Destructor.
     * 
     */
    ~opencl_mgr()
    {
        for (auto i : m_opencl_platforms)
        {
            delete i;
        }
        m_opencl_platforms.clear();
    };

    /**
     * @brief Returns the number of OpenCL platforms available.
     * 
     * @return      int         The number of OpenCL platforms available. Returns -1 if the operation failed.
     */
    int get_opencl_platform_count()
    {
        // get platform count
        cl_int err = clGetPlatformIDs(0, nullptr, &m_opencl_platform_count);

        if (err == CL_INVALID_VALUE)
        {
            std::cerr << "Supplied values to the function for getting the OpenCL platform IDs are invalid." << std::endl;
            return -1;
        }

        if (err == CL_OUT_OF_HOST_MEMORY)
        {
            std::cerr << "There was a failure to allocate resources required by the OpenCL implementation on the host." << std::endl;
            return -1;
        }

        return (int)m_opencl_platform_count;
    }

    /**
     * @brief Creates all sodecl::platform objects.
     * 
     * @return      int         The number of OpenCL platforms available. Returns -1 if the operation failed.
     */
    int create_opencl_platforms()
    {
        cl_platform_id *cpPlatform = new cl_platform_id[m_opencl_platform_count];

        // get all OpenCL platforms
        cl_int err = clGetPlatformIDs(m_opencl_platform_count, cpPlatform, nullptr);

        if (err == CL_INVALID_VALUE)
        {
            std::cerr << "Supplied values to the function for getting the OpenCL platform IDs are invalid." << std::endl;
            delete[] cpPlatform;
            return -1;
        }

        if (err == CL_OUT_OF_HOST_MEMORY)
        {
            std::cerr << "There was a failure to allocate resources required by the OpenCL implementation on the host." << std::endl;
            delete[] cpPlatform;
            return -1;
        }

        for (cl_uint i = 0; i < m_opencl_platform_count; i++)
        {
            m_opencl_platforms.push_back(new platform(cpPlatform[i]));
        }
        delete[] cpPlatform;

        return 1;
    }

    /**
     * @brief Sets the sodecl object to use the selected OpenCL device for the integration of the ODE model.
     * 
     * @param	platform_num	Index of selected OpenCL platform
     * @param	device_type		OpenCL device type
     * @param	device_num		Index of selected OpenCL device in the selected OpenCL platform
     * @return  int             Returns 1 if the operations were succcessfull or 0 if they were unsuccessful.
     */
    int choose_opencl_device(cl_uint platform_num, device_Type device_type, cl_uint device_num)
    {
        // Check if selected platform exist
        if (platform_num < 0 || platform_num > m_opencl_platform_count)
        {
            //cerr << "Selected platform number is out of bounds." << std::endl;
            // m_log->write("Selected platform number is out of bounds.\n");

            return 0;
        }

        // Check if selected device exist
        if (device_num < 0 || device_num > m_opencl_platforms[platform_num]->get_device_count())
        {
            //cerr << "Selected device number is out of bounds." << std::endl;
            // m_log->write("Selected device number is out of bounds.\n");
            return 0;
        }

        // If selected device type is not ALL (OpenCL type) check if selected device type exist
        if ((cl_device_type)device_type != (cl_device_type)device_Type::ALL)
        {
            if (m_opencl_platforms[platform_num]->m_devices[device_num]->type() != (cl_device_type)device_type)
            {
                //cerr << "Selected device is not of the type selected." << std::endl;
                // m_log->write("Selected device is not of the type selected.\n");
                return 0;
            }
        }

        //std::cout << "Selected platform: " << m_platforms[platform_num]->name().c_str() << std::endl;
        //std::cout << "Device name: " << m_platforms[platform_num]->m_devices[device_num]->name().c_str() << std::endl;
        ////std::cout << "Device type: " << m_platforms[platform_num]->m_devices[device_num]->type() << std::endl;

        // m_log->write("Selected platform name: ");
        // m_log->write(m_platforms[platform_num]->name().c_str());
        // m_log->write("\n");

        // m_log->write("Selected device name: ");
        // m_log->write(m_platforms[platform_num]->m_devices[device_num]->name().c_str());
        // m_log->write("\n");

        // m_log->write("Selected device OpenCL version: ");
        // m_log->write(m_platforms[platform_num]->m_devices[device_num]->version().c_str());
        // m_log->write("\n");

        m_selected_opencl_platform = platform_num;
        m_selected_opencl_device = device_num;
        m_selected_opencl_device_type = device_type;

        return 1;
    }
};
}

#endif // SODECL_OPENLC_MGR_HPP