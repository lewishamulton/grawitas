#include "xmlDumpParsingHandler.h"

#include <sstream>
#include <iostream>
#include <iomanip>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "coreTalkPageParsing.h"
#include "../output/outputWrapper.h"

namespace Grawitas {

	XmlDumpParsingHandler::XmlDumpParsingHandler(const std::set<Format>& formats, std::string output_folder)
		:_formats(formats),
		_output_folder(output_folder)
	{}

	void XmlDumpParsingHandler::HandleArticle(const WikiXmlDumpXerces::WikiPageData& data)
	{
		std::string title_filename = safeEncodeTitleToFilename(data.MetaData.at("title"));
		
		auto parsed_talk_page = parseTalkPage(data.Content);		

		std::size_t curId = 1;
		for (auto& sec : parsed_talk_page) {
			calculateIds(sec.second, curId);	
		}

		std::map<Format, std::string> formats_with_paths;
		for (auto format : _formats) 
			formats_with_paths.insert({ format, (_output_folder / (title_filename + FormatFileExtensions.at(format))).string() });

		output_in_formats_to_files(formats_with_paths, parsed_talk_page);
	}

}
