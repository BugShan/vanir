#include <Parser.h>
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
	po::options_description options("vanir runtime usage");
	po::variables_map cmd_line;
	try
	{
		options.add_options()
			("help", "Display help information")
			("module,m", po::value<std::string>()->required(), "Module name")
			("input,i", po::value<std::vector<std::string>>()->multitoken(), "Input file list")
			("output,o", po::value<std::string>()->required(), "Output file")
			("template,t", po::value<std::string>()->default_value("../mustache/vanir_runtime_template.txt"), "Output file")
			("compile_option", po::value<std::string>(), "Compile options")
			("display_message", "Display clang diagnostics")
			;
		po::store(po::parse_command_line(argc, argv, options), cmd_line);
		po::notify(cmd_line);

		if(cmd_line.count("help"))
		{
			std::cout << options << std::endl;
			return 0;
		}
	}
	catch(...)
	{
		std::cout << options << std::endl;
		return 0;
	}

	vanir::tool::ParserOption opt;
	opt.moduleName		= cmd_line.at("module").as<std::string>();
	opt.inputFileList	= cmd_line.at("input").as<std::vector<std::string>>();
	opt.outputFile		= cmd_line.at("output").as<std::string>();
	opt.templateFile	= cmd_line.at("template").as<std::string>();
	opt.displayDiagnostics = cmd_line.count("display_message") > 0;
	if(cmd_line.count("compile_option"))
		opt.arguments.push_back(cmd_line.at("compile_option").as<std::string>());
	opt.arguments.push_back("-x");
	opt.arguments.push_back("c++");
	opt.arguments.push_back("-std=c++11");
	//opt.arguments.push_back("-stdlib=libstdc++");
	opt.arguments.push_back("-D_VANIR_PARSER_");
	opt.arguments.push_back("-m32");

	vanir::tool::Parser parser(opt);
	parser.Init();
	parser.Parse();
	parser.Release();

	return 0;
}
