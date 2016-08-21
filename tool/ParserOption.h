#ifndef	_VANIR_TOOL_PARSEROPTION_H_
#define	_VANIR_TOOL_PARSEROPTION_H_

#include <string>
#include <vector>

namespace vanir
{
	namespace tool
	{
		struct ParserOption final
		{
			std::string					moduleName;
			std::vector<std::string>	inputFileList;
			std::string					outputFile;
			std::string					templateFile;

			bool						displayDiagnostics;
			std::vector<std::string>	arguments;
		};//struct ParserOption
	};//namespace tool
};//namespace vanir
#endif//_VANIR_TOOL_PARSEROPTION_H_
