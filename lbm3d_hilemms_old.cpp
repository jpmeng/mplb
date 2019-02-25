// Copyright 2017 the MPLB team. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

/** @brief Define the main iteration
 *  @author Jianping Meng
 **/
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include "boundary.h"
#include "evolution.h"
#include "evolution3d.h"
#include "flowfield.h"
#include "model.h"
#include "ops_seq.h"
#include "scheme.h"
#include "type.h"
#include "hilemms.h"
#include "setup_comput_domain.h"

// Code_modifcication needed
// Currently defining OPS 3d here. We need some mechanism to generate this automatically.
#define OPS_3D


int Max_no_Iterations  = 100000;
int check_point_Period = 1000;

int num_blocks = 1;
int blocks_size_x_y_z[] = {11, 11, 11};

int Num_Xi = 15;
int order_eq_dis_func = 2;
int lattice_dim = 3;
int Num_macroscopic_vars = 4;
int Num_components = 1;
int Thermal_problem = 0;
Real sound_speed = sqrt(3);

int Num_space_dim      = 3;
string CASE_NAME = "3D_Lid_Driven_Cavity";

int Block_index = 0;
int total_seg_each_dir[] = {1, 1, 1};
int Number_cells[] = {10, 10, 10};    // If more segments, provide num_cell for all segments in x direction, then y and then z.
Real end_position[] = {1.0, 1.0, 1.0}; //Length of lid in each direction.

Real Knudsen_number[] = {0.001};

// Face Type
int Bottom_bc_type = 1014;
int Top_bc_type = 1014;
int Left_bc_type = 1014;
int Right_bc_type = 1014;
int Front_bc_type = 1014;
int Back_bc_type = 1014;

int Face_type_bc_array[] = {Left_bc_type,   Right_bc_type,
                            Bottom_bc_type, Top_bc_type,
                            Front_bc_type,  Back_bc_type};

// Edge type
int Left_bottom_bc_type = 1014;
int Left_top_bc_type = 1014;
int Right_bottom_bc_type = 1014;
int Right_top_bc_type = 1014;
int Left_back_bc_type = 1014;
int Left_front_bc_type = 1014;
int Right_back_bc_type = 1014;
int Right_front_bc_type = 1014;
int Bottom_back_bc_type = 1014;
int Bottom_front_bc_type = 1014;
int Top_back_bc_type = 1014;
int Top_front_bc_type = 1014;

int Edge_type_bc_array[] = {Left_bottom_bc_type,  Left_top_bc_type,
                            Right_bottom_bc_type, Right_top_bc_type,
                            Left_back_bc_type,    Left_front_bc_type,
                            Right_back_bc_type,   Right_front_bc_type,
                            Bottom_back_bc_type,  Bottom_front_bc_type,
                            Top_back_bc_type,     Top_front_bc_type};

// Corner type
int Left_bottom_back_bc_type = 1014;
int Left_bottom_front_bc_type = 1014;
int Left_top_back_bc_type = 1014;
int Left_top_front_bc_type = 1014;
int Right_bottom_back_bc_type = 1014;
int Right_bottom_front_bc_type = 1014;
int Right_top_back_bc_type = 1014;
int Right_top_front_bc_type = 1014;

int Corner_type_bc_array[] = {Left_bottom_back_bc_type,  Left_bottom_front_bc_type,
                              Left_top_back_bc_type,     Left_top_front_bc_type,
                              Right_bottom_back_bc_type, Right_bottom_front_bc_type,
                              Right_top_back_bc_type,    Right_top_front_bc_type};

Real InletMacrovars[]  = {1, 0, 0, 0};
Real OutletMacrovars[] = {1, 0, 0, 0};
Real TopMacrovars[]    = {1, 0.01, 0, 0};
Real BottomMacrovars[] = {1, 0, 0, 0};
Real BackMacroVars[] = {1, 0, 0, 0};
Real FrontMacroVars[] = {1, 0, 0, 0};

Real Initial_value_macro_vars[] = {1, 0, 0,  0};

int Num_bound_halo_pts = 1;
int Halo_Num = 0;
int Halo_depth = 0; 
int Scheme_halo_points = 1;

void Preprocessor_lbm3d_hilemms()
{
    #if 0
    DefineCase(CASE_NAME, Num_space_dim);
    ReadBlockDimensions(num_blocks, blocks_size_x_y_z);
    DefineLattice(Num_Xi, order_eq_dis_func, lattice_dim, Num_macroscopic_vars, Num_components, Thermal_problem, sound_speed);

    DefineHaloNumber(Halo_Num, Halo_depth, Scheme_halo_points,Num_bound_halo_pts);

    Setup_Stencil_Model(Num_Xi,lattice_dim);
    //Setup_Stencil_Model();

    BlockSegmentInfo(Block_index, total_seg_each_dir, Number_cells, end_position, Num_space_dim);

    //cout<<"Check! Hi I am in main and I finished BlockSegmentInfo \n";

    //ReadNodeType(Block_index, Bottom_bc_type, Top_bc_type, Left_bc_type, Right_bc_type,
    //             Left_bottom_bc_type, Left_top_bc_type, Right_bottom_bc_type, Right_top_bc_type);

    //ReadNodeType3D(int blockIndex, int* Face_Type, int* Edge_Type, int* Corner_Type)
    ReadNodeType3D(Block_index, Face_type_bc_array, Edge_type_bc_array, Corner_type_bc_array);

    Initialise_Macrovars_Domain(Initial_value_macro_vars);

    //cout<<"Check! Hi I am in Simulate_lbm2d_hilemms and I initialised variables. \n";


    DefineIterationParamaeters(Max_no_Iterations, check_point_Period);
    DefineKnudsenNo(Knudsen_number);

    //simulate(InletMacrovars, Left_bc_type,  OutletMacrovars, Right_bc_type, 
    //          TopMacrovars, Top_bc_type, BottomMacrovars, Bottom_bc_type);

    //DefineBC2d(InletMacrovars, Left_bc_type,  OutletMacrovars, Right_bc_type, 
    //           TopMacrovars, Top_bc_type, BottomMacrovars, Bottom_bc_type);
    #endif
}


int main(int argc, char** argv) {
    // initialize sizes using global values

    /**-------------------------- Initialisation --------------------------**/

    // OPS initialisation
    ops_init(argc, argv, 5);
    double ct0, ct1, et0, et1;
    ops_timers(&ct0, &et0);

    #if 0
    Preprocessor_lbm3d_hilemms();

    //cout<<"Check! Hi I am in main and I finished Preprocessor_lbm3d_hilemms\n";
    
    //simulate(InletMacrovars, Left_bc_type,  OutletMacrovars, Right_bc_type, 
    //         TopMacrovars, Top_bc_type, BottomMacrovars, Bottom_bc_type, Num_bound_halo_pts);

    simulate3D(InletMacrovars, Left_bc_type,  OutletMacrovars, Right_bc_type, 
               TopMacrovars,   Top_bc_type,   BottomMacrovars, Bottom_bc_type, 
               FrontMacroVars, Front_bc_type, BackMacroVars,   Back_bc_type, Num_bound_halo_pts);
    #endif

    //TreatBlockBoundary3D(blockIndex, componentID, macroVarsBoundCond, rangeBoundCond, vtType);
    ops_timers(&ct1, &et1);
    //ops_timing_output(stdout);
    ops_exit();
}

