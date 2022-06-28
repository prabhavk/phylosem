#include <stdio.h>
#include <string>
#include "mstBackbone.h"
#include <iostream>
#include <experimental/filesystem>
// #include <boost/filesystem.hpp>
#include <sys/stat.h>
using namespace std;
namespace fs = std::experimental::filesystem;

int main(int argc, char **argv)
{	
	string path_to_alignment_file;
	fs::path alignment_file_path_obj;
	fs::path prefix_path_obj;
    string prefix_for_output_files;
	string path_to_directory;
    int size_of_subtree;
 	struct stat buffer;
	// bool alignment_file_not_set = 0;
	bool flag_size_of_subtree = 0;
	bool flag_prefix = 0;
	// bool localPhyloOnly = 0;
	bool flag_modelSelection = 0;
	// bool useChowLiu = 1;
	string modelForRooting = "UNREST";
	string arg_localPhyloOnly;
	string arg_modelSelection;
	string arg_chowliu;
    if (argc < 2) {        
        cerr << "Example for performing mst-constrained tree construction: " << argv[0] << " --seq alignment.fas --size size_of_subtree --out prefix_for_output" << endl;
		cerr << endl ;
		cerr << "Example for performing model selection: " << argv[0] << " --seq alignment.fas --out prefix_for_output --perform_model_selection true " << endl;
        return (-1);
    } else {        
        // parse arguments            
        for (int i = 1; i < argc ; i++) {
        // path to multiple sequence alignment file
            if (strcmp(argv[i], "--seq") == 0) {				
                if (i < argc -1) {					
                    path_to_alignment_file = argv[++i];
					cout << "alignment file name is " << path_to_alignment_file << endl;
					if (stat (path_to_alignment_file.c_str(), &buffer) != 0) { // check if input file exists
						cout << "Please check if the input filename is correct" << endl;
						exit (-1);
					}
					alignment_file_path_obj = path_to_alignment_file;
                }
        // prefix_to_output_files (e.g. prefix is "covid-19_size_42" and the alignment is in directory "/foo/bar/data/")		
            } else if (strcmp(argv[i], "--out") == 0) {
                if (i < argc -1) {
					flag_prefix = 1;
                    prefix_for_output_files = argv[++i];
					// prefix_for_output_files = alignment_file_path_obj.parent_path().string() + prefix_for_output_files;
					prefix_path_obj =  alignment_file_path_obj.parent_path();
					prefix_path_obj /= prefix_for_output_files;
					cout << "prefix for output files is " << prefix_for_output_files << endl;					
                }
        // size of subtree Vs
            } else if (strcmp(argv[i], "--size") == 0) {
                if (i < argc -1) {
					flag_size_of_subtree = 1;
                    size_of_subtree = stoi(argv[++i]);
                }
			} else if (strcmp(argv[i], "--perform_model_selection") == 0) {
                if (i < argc -1) {
					arg_modelSelection = argv[++i];
					if (strcmp(arg_modelSelection.c_str(), "true") == 0) {
						flag_modelSelection = 1;
					} else if (strcmp(arg_modelSelection.c_str(), "True") == 0) {
						flag_modelSelection = 1;
					}
                }
			} else if (strcmp(argv[i], "--help") == 0) {
				cout << "Example for mst-constrained tree construction: " << argv[0] << " --seq alignment.fas --size size_of_subtree --out prefix_for_output" << endl;
				cout << endl;
				cout << "Example for model selection: " << argv[0] << " --seq alignment.fas --perform_model_selection true --out prefix_for_output" << endl;
			}
        }

		if (!flag_size_of_subtree) {
			size_of_subtree = 10;
		}

		if (!flag_prefix) {
			prefix_path_obj =  alignment_file_path_obj.parent_path();
			prefix_path_obj /= "mst-backbone_default_output";			
			// prefix_for_output_files = path_obj.parent_path().string() + "mst_backbone";
		}
		MSTBackbone MSTBackboneObj(path_to_alignment_file, size_of_subtree, prefix_path_obj.string(),flag_modelSelection);
		// MSTBackbone MSTBackboneObj(path_to_alignment_file, size_of_subtree, prefix_path_obj.string(),localPhyloOnly,modelSelection,modelForRooting,useChowLiu);
    }

	return 0;
} 