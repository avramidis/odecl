%module pysodecl
%{
/* Put header files here or function declarations like below */
#include <string>
#include <vector>
extern std::vector<double> sodeclcall( std::vector<double> a_t0,
                                        std::vector<double> a_y0,
                                        std::vector<double> a_params,
                                        int a_platform,
                                        int a_device,
                                        std::string a_system,
                                        int a_solver_type,
                                        int a_orbits,
                                        int a_equats,
                                        int a_nparams,
                                        int a_nnoi,
                                        double a_dt,
                                        double a_tspan,
                                        int a_ksteps,
                                        int a_local_group_size);
%}

%include "std_string.i"
%include "std_vector.i"
namespace std {
    %template(DoubleVector) vector<double>;
};

extern std::vector<double> sodeclcall( std::vector<double> a_t0,
                                        std::vector<double> a_y0,
                                        std::vector<double> a_params,
                                        int a_platform,
                                        int a_device,
                                        std::string a_system,
                                        int a_solver_type,
                                        int a_orbits,
                                        int a_equats,
                                        int a_nparams,
                                        int a_nnoi,
                                        double a_dt,
                                        double a_tspan,
                                        int a_ksteps,
                                        int a_local_group_size);
