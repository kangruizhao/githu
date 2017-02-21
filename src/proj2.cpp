#include "p2.h"
#include"netlist.h"	
#include <sstream>
#include <assert.h>







		int main(int argc, char *argv[])
		{
			if (argc < 2)
			{
				std::cerr << "You should provide a file name." << std::endl;
				return -1;
			}// verify that argv[1] exists 

			std::string evl_file = argv[1];
			std::string module_name; 
			evl_wires wires; 
			evl_componets comps; 
			if (!parse_evl_file(argv[1], module_name, wires, comps)) return -1;
			
			
			evl_wires_table wires_table; 
			if (!make_wires_table(wires, wires_table)) return -1;
			netlist nl; 
			if (!nl.create(wires, comps, wires_table)) return -1;
			std::string nl_file = std::string(argv[1]) + ".netlist"; 
			
			//
			//nl.save(nl_file, module_name);
			//std::cout << comps.front().name << std::endl;
			
			nl.simulate(std::string(argv[1]), 1000);
			 return 0;
		}

	