#include<fstream>
#include<iostream>
#include<string>
#include<iterator>
#include<regex>
#include<boost/optional.hpp>

using namespace std::string_literals;

struct Default{};
struct Reverse{};

std::string::const_iterator find_value_of(const std::string& str,const std::string& search_str,std::size_t to,const Default&)
{
	return std::next(std::next(std::next(str.cbegin(),str.find(search_str)),search_str.size()),to);
}

std::string::const_iterator find_value_of(const std::string& str,const std::string& search_str,std::size_t to,const Reverse&)
{
	return std::next(std::next(std::next(str.cbegin(),str.rfind(search_str)),search_str.size()),to);
}

boost::optional<std::string> make_input_string(std::string&& str)
{
	std::ifstream ifs(std::move(str));
	if(ifs.fail())return {};
	
	std::string file_="",file="";
	while(std::getline(ifs,file_)){
		if(file_.find("#")==std::string::npos){
			file+=file_;
			file+="\n"s;
		}
	}
	return file;
}

std::string make_output(std::string&& file)
{
	std::string output="";

	output+="Log Level :";
	output+=*find_value_of(file,"log_level"s,1,Default{})+"\n"s;

	output+="Frequency :";
	output+=*find_value_of(file,"frequency"s,1,Reverse{})+"\n"s;

	output+="Framerate :";
	output+=*find_value_of(file,"framerate"s,1,Default{});
	output+=*find_value_of(file,"framerate"s,2,Default{});
	output+="\n";
	
	output+="Quality :";
	output+=*find_value_of(file,"quality"s,1,Default{});
	output+=*find_value_of(std::move(file),"quality"s,2,Default{});
	output+="\n";

	output+="Outputting MPEG movies :";
	output+=*find_value_of(file,"ffmpeg_output_movies"s,1,Default{});
	output+=*find_value_of(file,"ffmpeg_output_movies"s,2,Default{});
	output+="\n";

	output+="Locate motion mode :";
	output+=*find_value_of(file,"locate_motion_mode"s,1,Default{});
	output+=*find_value_of(file,"locate_motion_mode"s,2,Default{});
	output+="\n";

	output+="\nStarting motion";
	
	return output;
}

int main(const int argc,const char* argv[])
{
	std::string file_src;
	if(argc<2){
		file_src="/etc/motion/motion.conf";
	}else{
		file_src=argv[2];
		argv[2]=nullptr;
	}

	auto input=make_input_string(std::move(file_src));
	if(!input){
		std::cerr<<"Fail to load config file of motion"<<std::endl;
		return -1;
	}
	std::cout<< make_output(std::move(input.value())) <<std::endl;
}
