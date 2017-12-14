#pragma once

#include <iostream>
#include <set>

#include "../talkPageParser/models.h"

namespace Grawitas {
	void listToCsv(std::ostream& ostr, const std::vector<Comment>& parsedTalkPage, const std::set<std::string> included_fields = {"id", "parent_id", "user", "date", "level", "text", "section", "article"});
}

