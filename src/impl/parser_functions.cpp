
/*
	Copyright (C) 2021 Joshua Boudreau <jboudreau@45drives.com>

	This file is part of lib45d_conf.

	lib45d_conf is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	lib45d_conf is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with lib45d_conf.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "parser_functions.hpp"
#include <string>

void strip_whitespace(std::string &str) {
	size_t start, end;
	start = str.find_first_not_of(" \t");
	end = str.find_last_not_of(" \t");
	if (start == end) {
		str.clear();
		return;
	}
	str.assign(str, start, end - start + 1);
}

void remove_comments(std::string &str) {
	size_t comment_pos = str.find_first_of('#');
	if (comment_pos == std::string::npos)
		return;
	str.erase(comment_pos);
}

inline bool check_if_heading(const std::string &record) {
	size_t first_not_space = record.find_first_not_of(" \t");
	if (first_not_space == std::string::npos)
		return false; // all whitespace
	if (record[first_not_space] != '[') // first non-whitespace must be '['
		return false; // character other than '['
	size_t closing_bracket = record.find(']', first_not_space);
	if (closing_bracket == std::string::npos)
		return false; // no closing ']'
	return true; // section header found
}

RecordType check_record_type(const std::string &record) {
	if (check_if_heading(record))
		return RecordType::HEADING;
	if (record.find('=') != std::string::npos)
		return RecordType::ENTRY;
	std::string::const_iterator itr = record.begin();
	while (itr != record.end() && (*itr == ' ' || *itr == '\t'))
		++itr;
	if (itr == record.end() || *itr == '#')
		return RecordType::EMPTY;
	return RecordType::UNK;
}
