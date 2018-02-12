#ifndef SODECL_EULER_HPP
#define SODECL_EULER_HPP

#include "sodecl.hpp"

namespace sodecl
{

/**
 * @brief Abstract class that acts as an interface for the implementation of different ODE or SDE solvers.
 * 
 */
class euler : public solver_interface
{
    /**
     * @brief Default constructor.
     * 
     */
    euler() : solver_interface()
    {
    }

    /**
     * @brief Virtual destructor.
     * 
     */
    ~euler()
    {
    }

    /**
     * @brief Forms the OpenCL kernel string(s).
     * 
     * @return  int         Returns 1 if the operations were succcessful or 0 if they were unsuccessful.
     */
    int create_kernel_string(){};

    /**
     * @brief Creates the OpenCL buffers needed for the solver.
     * 
     * @param	context		OpenCL cl_context.
     * @param	list_size	Size of the buffers in number of data points.
     * @param	equat_num	Number of equations.
     * @param   param_num	Number of parameters.
     * @return  int         Returns 1 if the operations were succcessful or 0 if they were unsuccessful.
     */
    int create_buffers(cl_context context, int list_size, int equat_num, int param_num)
    {
    }

    /**
     * @brief Writes data in the OpenCL memory buffers.
     * 
     * @param	commands	OpenCL command queue.
     * @param	list_size	Number of data points to be written in the OpenCL memory buffers.
     * @param	equat_num	Number of equations of the ODE or SDE system.
     * @param	param_num	Number of parameters of the ODE or SDE system.
     * @return  int         Returns 1 if the operations were succcessful or 0 if they were unsuccessful.
     */
    int write_buffers(cl_command_queue commands, int list_size, int equat_num, int param_num)
    {
    }

    /**
     * Setups the selected ODE or SDE solver OpenCL kernel source.
     *
     * @return 1 if the operations were succcessfull or 0 if they were unsuccessful
     */
    /**
     * @brief Setups the selected ODE or SDE solver OpenCL kernel source.
     * 
     * @return  int         Returns 1 if the operations were succcessful or 0 if they were unsuccessful.
     */
    int setup_solver()
    {
    }

    /**
     * @brief Executes the ODE or SDE solver on the selected OpenCL device.
     * 
     * @return  int         Returns 1 if the operations were succcessful or 0 if they were unsuccessful.
     */
    int run_solver()
    {
    }
};
}

#endif // SODECL_EULER_HPP